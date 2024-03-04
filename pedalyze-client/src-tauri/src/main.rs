#![cfg_attr(
    all(not(debug_assertions), target_os = "windows"),
    windows_subsystem = "windows"
)]

use database::config::ConfigDatabase;
use tauri::{async_runtime::Mutex, App, Wry};

mod bridge;
mod communication;
mod database;
mod routines;

use bridge::commands::{
    communications::upload_routine, config::get_config, routines::save_routine,
};
use communication::{
    serial_process,
    upload::{UploadBuffer, UploadBufferMutex},
};

fn setup(app: &mut App<Wry>) -> Result<(), Box<dyn std::error::Error>> {
    let app_handle = app.handle();

    tauri::async_runtime::spawn(async move { serial_process(&app_handle).await });

    Ok(())
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![
            save_routine,
            upload_routine,
            get_config
        ])
        .manage(UploadBufferMutex(Mutex::new(UploadBuffer::new())))
        .manage(ConfigDatabase)
        .setup(setup)
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
