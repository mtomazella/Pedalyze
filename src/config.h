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
#define MAX_TABS 6

#define ENCODER_TEST_TAB_MENU_ID 3
#define ENCODER_TEST_TAB_NAME "Encoder Test"
#define MIDI_TEST_TAB_MENU_ID 4
#define MIDI_TEST_TAB_NAME "MIDI Test"
#define MATRIX_TEST_TAB_MENU_ID 5
#define MATRIX_TEST_TAB_NAME "Matrix Test"
#endif

// Matrix
#define MATRIX_HEIGHT 3
#define MATRIX_WIDTH 4
#define MATRIX_LENGTH 12
#define COL1 7
#define COL2 1
#define COL3 5
#define COL4 2
#define ROW1 3
#define ROW2 4
#define ROW3 6

// Encoder
#define ENCODER_OPTIMIZE_INTERRUPTS
#define ENCODER_CLK 5
#define ENCODER_DT 7
#define ENCODER_SW 8

// Menu switch
#define MENU_SWITCH 9

// Channels
#define MAX_CHANNELS 5
#define CH1 21
#define CH2 20
#define CH3 19
#define CH4 18
#define CH5 10
/*
  Vo = (VR2)/(R1+R2)
  V = 5V
  R1 = 100k
  R2 = 39k
  Vo = (39k)/(100k+39k) * 5V = 1.95V
  This is the amount lost to the voltage divider
  P = 1023/5V = 204.6
  1.95V * 204.6 = 399.57
*/
// #define CHANNEL_LOWER_LIMIT 400
#define CHANNEL_LOWER_LIMIT 15