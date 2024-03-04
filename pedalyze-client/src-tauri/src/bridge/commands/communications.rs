use tauri::State;

use crate::{communication::upload::UploadBufferMutex, routines::Routine};

#[tauri::command]
pub async fn upload_routine(
    routine: Routine,
    upload_buffer_state: State<'_, UploadBufferMutex>,
) -> Result<(), ()> {
    let mut upload_buffer = upload_buffer_state.0.lock().await;
    return upload_buffer.new_upload(routine);
}
