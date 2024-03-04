use serde::{Deserialize, Serialize};
use std::str;
use tauri::Manager;

#[derive(Clone, Copy, Deserialize)]
pub struct RawDataBundle {
    tp: f64,  // temperature
    t: f64,   // tension
    tg: f64,  // target current
    c: f64,   // actual current
    f: i8,    // fan percentage
    clk: u32, // time in milliseconds
}

impl TryFrom<&str> for RawDataBundle {
    type Error = serde_json::Error;

    fn try_from(string_data: &str) -> Result<Self, serde_json::Error> {
        let json_data: Result<Self, serde_json::Error> = serde_json::from_str(string_data);
        json_data
    }
}

#[derive(Clone, Copy, Serialize)]
pub struct DataBundle {
    temperature: f64,
    tension: f64,
    target_current: f64,
    actual_current: f64,
    fan_percentage: i8,
    power: f64,
    routine_time: u32,
}

impl From<RawDataBundle> for DataBundle {
    fn from(raw: RawDataBundle) -> Self {
        DataBundle {
            actual_current: raw.c,
            fan_percentage: raw.f,
            target_current: raw.tg,
            temperature: raw.tp,
            tension: raw.t,
            power: raw.t * raw.c,
            routine_time: raw.clk,
        }
    }
}

pub fn handle_new_measurement<R: tauri::Runtime>(manager: &impl Manager<R>, str_metrics: &str) {
    let parsed_json = RawDataBundle::try_from(str_metrics);
    let raw = match parsed_json {
        Ok(value) => value,
        Err(_) => {
            println!("Invalid data format. Message received: {}", str_metrics);
            return ();
        }
    };
    let data = DataBundle::from(raw);

    // let mut file = OpenOptions::new()
    //     .write(true)
    //     .append(true)
    //     .open("/home/tomazella/accl/temp.txt")
    //     .unwrap();

    // if let Err(e) = writeln!(
    //     file,
    //     "time: {}  tension: {}  target: {}  current: {}",
    //     data.routine_time, data.tension, data.target_current, data.actual_current
    // ) {
    //     eprintln!("Couldn't write to file: {}", e);
    // }

    emit_new_metrics_event(manager, data);
}

fn emit_new_metrics_event<R: tauri::Runtime>(manager: &impl Manager<R>, payload: DataBundle) {
    manager.emit_all("new_metrics", payload).unwrap();
}

pub fn define_new_str_buffer(old_buffer: String, value: &str) -> String {
    let buffer_has_beginning = old_buffer.starts_with('{');
    let mut split_data = value.split_inclusive('}');
    let data_has_ending = value.contains('}');
    let data_has_beginning = value.contains('{');

    let mut new_buffer = "".to_owned();

    if buffer_has_beginning {
        if data_has_ending || !data_has_beginning && !data_has_ending {
            new_buffer.push_str(&old_buffer);
            new_buffer.push_str(split_data.nth(0).unwrap());
        }
    } else {
        if data_has_beginning {
            let beginning = split_data.find(|item| item.contains('{'));
            match beginning {
                Some(b) => {
                    new_buffer.push_str(b);
                }
                None => new_buffer = "".to_owned(),
            }
        }
    }
    return new_buffer;
}
