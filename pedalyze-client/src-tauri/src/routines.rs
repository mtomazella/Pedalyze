use std::str::FromStr;

use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize, Clone)]
pub enum RoutineCurveType {
    Linear,
    Monotone,
    StepAfter,
}

impl RoutineCurveType {
    pub fn to_string(&self) -> String {
        match self {
            RoutineCurveType::Linear => String::from_str("Linear").unwrap(),
            RoutineCurveType::Monotone => String::from_str("Monotone").unwrap(),
            RoutineCurveType::StepAfter => String::from_str("StepAfter").unwrap(),
        }
    }
}

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct RoutinePoint {
    pub time: f32,
    pub current: f32,
}

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Routine {
    pub name: String,
    pub curve_type: RoutineCurveType,
    pub loops: bool,
    pub points: Vec<RoutinePoint>,
}

impl Routine {
    pub fn new() -> Routine {
        Routine {
            name: "EMPTY_ROUTINE".to_owned(),
            curve_type: RoutineCurveType::Linear,
            loops: false,
            points: vec![],
        }
    }

    #[allow(dead_code)]
    pub fn is_empty(&self) -> bool {
        self.name == "EMPTY_ROUTINE".to_owned()
    }
}
