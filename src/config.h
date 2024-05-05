#pragma once

// Macro config
#define ENABLE_TEST_TABS

// Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Menu
#define MAX_TABS 3    // exclude test tabs
#define INITIAL_TAB 0 // use to start in a tab that is not in the switch

#define DEBOUNCE_INTERVAL 100
#define DOUBLE_CLICK_INTERVAL 200
#define HOLD_CLICK_INTERVAL 600

#define CONTROL_TAB_MENU_ID 0
#define CONTROL_TAB_NAME "Control"
#define MIDI_TAB_MENU_ID 1
#define MIDI_TAB_NAME "MIDI"
#define CONFIG_TAB_MENU_ID 2
#define CONFIG_TAB_NAME "Config"

#ifdef ENABLE_TEST_TABS
#define MAX_TABS 4

#define ENCODER_TEST_TAB_MENU_ID 3
#define ENCODER_TEST_TAB_NAME "Encoder Test"
#define MIDI_TEST_TAB_MENU_ID 4
#define MIDI_TEST_TAB_NAME "MIDI Test"
#endif

// Matrix
#define MATRIX_LENGTH 12

// Encoder
#define ENCODER_OPTIMIZE_INTERRUPTS
#define ENCODER_CLK 5
#define ENCODER_DT 7
#define ENCODER_SW 8

// Menu switch
#define MENU_SWITCH 9