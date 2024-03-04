use std::str::FromStr;

use super::generic::FileDatabase;

pub struct ConfigDatabase;

impl FileDatabase for ConfigDatabase {
    fn db_file_name(&self) -> String {
        return String::from_str("config.json").unwrap();
    }

    fn new(&self) -> Self {
        return Self;
    }
}
