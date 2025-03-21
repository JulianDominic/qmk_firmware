// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "oled_screens.h"
#include QMK_KEYBOARD_H
#define DIP_SWITCH 0

#ifdef OLED_ENABLE
static void cls(void) {
    oled_set_cursor(0, 1);
    oled_write_raw_P(CLEAR_SCREEN, sizeof(CLEAR_SCREEN));
}

static void state00(void) {
    cls();
    oled_set_cursor(0, 1);
    oled_write_raw_P(WINDOWS_LOGO, sizeof(WINDOWS_LOGO));
}

static void state01(void) {
    cls();
    oled_set_cursor(0, 1);
    oled_write_raw_P(LATEX_LOGO, sizeof(LATEX_LOGO));
}

static void state02(void) {
    cls();
    oled_set_cursor(0, 1);
    oled_write_raw_P(RICK_ROLL_QR, sizeof(RICK_ROLL_QR));
}

bool oled_task_user(void) {
    oled_set_cursor(0, 1);
    return false;
}
#endif

#ifdef DIP_SWITCH_ENABLE
#define NUM_STATES 3

typedef void (*f)(void);
f states[NUM_STATES] = { &state00, &state01, &state02 };
int state = 0;

bool dip_switch_update_user(uint8_t index, bool active) { 
    if (index == DIP_SWITCH) {
        if (active) {
            states[state]();
            layer_off(state);
            state = (state + 1) % NUM_STATES;
        } else {
            states[state]();
            layer_on(state);
        }
    }
    return true;
}
#endif

enum custom_keycodes {
    LATEX_TEXTBF = SAFE_RANGE,
    LATEX_TEXT,
    LATEX_MATHRM,
    LATEX_DISPLAYSTYLE,
    MD_TABLE_HEADER_BODY,
    MD_TABLE_ALIGNMENT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LATEX_TEXTBF:
            if (record->event.pressed) {
                SEND_STRING("\\textbf");
            }
            break;

        case LATEX_TEXT:
            if (record->event.pressed) {
                SEND_STRING("\\text");
            }
            break;
        
        case LATEX_MATHRM:
            if (record->event.pressed) {
                SEND_STRING("\\mathrm");
            }
            break;
        
        case LATEX_DISPLAYSTYLE:
            if (record->event.pressed) {
                SEND_STRING("\\displaystyle");
            }
            break;

        case MD_TABLE_HEADER_BODY:
            if (record->event.pressed) {
                SEND_STRING("|||");
            }
            break;

        case MD_TABLE_ALIGNMENT:
            if (record->event.pressed) {
                SEND_STRING("|:-|:-|");
            }
            break;
        }
    return true;
};

#ifdef LEADER_ENABLE
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    // Leader, KC_NO
    if (leader_sequence_one_key(KC_F19)) {
        tap_code16(KC_SYSTEM_SLEEP);
    }
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        KC_AUDIO_VOL_DOWN,    KC_AUDIO_VOL_UP,    KC_AUDIO_MUTE,
        KC_GRAVE,    KC_LEFT_ALT,    KC_TAB,
        LCTL(KC_C),    LCTL(KC_V),    KC_PRINT_SCREEN
    ),
    [1] = LAYOUT_ortho_3x3(
        LATEX_TEXTBF,    LATEX_TEXT,    KC_NO,
        LATEX_MATHRM,    LATEX_DISPLAYSTYLE,    KC_NO,
        MD_TABLE_HEADER_BODY,    MD_TABLE_ALIGNMENT,    KC_NO
    ),
    [2] = LAYOUT_ortho_3x3(
        KC_NO,    KC_NO,    KC_NO,
        KC_NO,    KC_NO,    KC_NO,
        KC_NO,    QK_LEADER,    KC_F19
    )
};
