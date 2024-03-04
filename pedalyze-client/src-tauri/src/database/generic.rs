use platform_dirs::AppDirs;
use std::{
    fs::{read_to_string, File},
    path::PathBuf,
};

#[allow(dead_code)]
pub enum FileDatabaseError {
    FailedRead,
}

pub trait FileDatabase {
    fn db_file_name(&self) -> String;

    fn get_path(&self) -> PathBuf {
        return AppDirs::new(Some("accl-client"), false)
            .unwrap()
            .config_dir
            .join(self.db_file_name());
    }

    fn create_if_not_exist(&self) {
        let path = self.get_path();

        if !path.exists() {
            match File::create(path) {
                Err(_) => panic!("Failed to create file"),
                _ => return,
            }
        }
    }

    fn read_file(&self) -> Result<String, FileDatabaseError> {
        self.create_if_not_exist();
        let path = self.get_path();

        return match read_to_string(path) {
            Ok(value) => Ok(value),
            Err(_) => Err(FileDatabaseError::FailedRead),
        };
    }

    fn new(&self) -> Self;
}
