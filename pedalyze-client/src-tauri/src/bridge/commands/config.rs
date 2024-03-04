#[tauri::command]
pub async fn get_config() -> Result<(), String> {
    println!("Get config test");
    Ok(())
}
