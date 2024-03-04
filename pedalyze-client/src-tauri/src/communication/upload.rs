use serde::{Serialize, __private::from_utf8_lossy};
use serialport::SerialPort;
use std::{
    str::FromStr,
    time::{Duration, Instant},
};
use tokio::sync::{Mutex, MutexGuard};

use crate::routines::{Routine, RoutinePoint};

#[derive(Debug, Clone)]
pub struct UploadBuffer {
    pub routine: Routine,
    pub buffer: String,
    pub zero: Instant,
    pub last_upload_finished: Instant,
    pub last_upload_request: Instant,
    pub last_read_confirmation_request: Instant,
    pub last_read_confirmation_received: Instant,
    pub next_chunk_to_send: usize,
}

impl UploadBuffer {
    pub fn new() -> UploadBuffer {
        let now = Instant::now();
        return UploadBuffer {
            routine: Routine::new(),
            buffer: "".to_owned(),
            zero: now.clone(),
            last_upload_finished: now.clone(),
            last_upload_request: now.clone(),
            last_read_confirmation_request: now.clone(),
            last_read_confirmation_received: now.clone(),
            next_chunk_to_send: 0,
        };
    }

    pub fn is_initialized(&self) -> bool {
        return !self.last_upload_request.eq(&self.zero);
    }

    pub fn upload_pending(&self) -> bool {
        if !self.is_initialized() {
            return false;
        };
        return self.last_upload_request.gt(&self.last_upload_finished);
    }

    pub fn waiting_for_read_confirmation(&self) -> bool {
        if !self.is_initialized() {
            return false;
        }
        return self
            .last_read_confirmation_request
            .gt(&self.last_read_confirmation_received);
    }

    pub fn read_confirmation_timeout(&self) -> bool {
        if !self.is_initialized() || !self.waiting_for_read_confirmation() || !self.upload_pending()
        {
            return false;
        }
        return Instant::now()
            .duration_since(self.last_read_confirmation_received)
            .ge(&Duration::from_secs(10));
    }

    pub fn mark_upload_complete(&mut self) {
        self.last_upload_finished = Instant::now();
        self.next_chunk_to_send = 0;
    }

    pub fn new_upload(&mut self, routine: Routine) -> Result<(), ()> {
        if self.upload_pending() {
            return Err(());
        }

        let new_string_buffer = serde_json::to_string(&(routine.clone())).unwrap();
        self.routine = routine;
        self.buffer = new_string_buffer;
        self.last_upload_request = Instant::now();
        self.last_read_confirmation_received = Instant::now();

        Ok(())
    }
}

pub struct UploadBufferMutex(pub Mutex<UploadBuffer>);

#[derive(Debug, Serialize, Clone)]
pub struct JsonRoutinePoint {
    time: String,
    current: String,
}

impl From<&RoutinePoint> for JsonRoutinePoint {
    fn from(point: &RoutinePoint) -> Self {
        JsonRoutinePoint {
            time: point.time.to_string(),
            current: point.current.to_string(),
        }
    }
}

#[derive(Debug, Serialize, Clone)]
struct JsonRoutine {
    pub name: String,
    pub curve_type: String,
    pub loops: String,
    pub points: Vec<JsonRoutinePoint>,
}

impl From<&Routine> for JsonRoutine {
    fn from(routine: &Routine) -> Self {
        JsonRoutine {
            name: routine.name.clone(),
            curve_type: routine.curve_type.clone().to_string(),
            loops: if routine.loops == true {
                String::from_str("true").unwrap()
            } else {
                String::from_str("false").unwrap()
            },
            points: routine
                .points
                .clone()
                .iter()
                .map(|point| JsonRoutinePoint::from(point))
                .collect(),
        }
    }
}

fn stringify_routine(routine: &Routine) -> String {
    return serde_json::to_string(&JsonRoutine::from(routine)).unwrap();
}

pub fn handle_routine_upload(
    serial_port: &mut Box<dyn SerialPort>,
    upload_buffer: &MutexGuard<UploadBuffer>,
) -> bool {
    let string_routine = stringify_routine(&upload_buffer.routine);
    let chunks: Vec<&[u8]> = string_routine.as_bytes().chunks(50).collect();

    println!(
        "Writing: {}",
        from_utf8_lossy(chunks[upload_buffer.next_chunk_to_send])
    );
    match serial_port.write(chunks[upload_buffer.next_chunk_to_send]) {
        Err(_) => println!("Failed to write to serial"),
        _ => ()
    }

    if upload_buffer.next_chunk_to_send == chunks.len() - 1 {
        return true;
    } else {
        return false;
    }
}
