use crate::routines::Routine;

#[tauri::command]
pub fn save_routine(routine: Routine) {
    println!("{:?}", routine)
}
