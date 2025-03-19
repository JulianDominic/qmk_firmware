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
    oled_write_raw_P(RICK_ROLL_QR, sizeof(RICK_ROLL_QR));
}

bool oled_task_user(void) {
    oled_set_cursor(0, 1);
    return false;
}
#endif

#ifdef DIP_SWITCH_ENABLE
typedef void (*f)(void);
f states[2] = {&state00, &state01};
int state = 0;
bool dip_switch_update_user(uint8_t index, bool active) { 
    if (index == DIP_SWITCH) {
        if (active) {
            states[state]();
            state = (state + 1) % 2;
        } else {
            states[state]();
        }
    }
    return true;
}
#endif

enum custom_keycodes {
    LATEX_MATHBB = SAFE_RANGE,
    LATEX_FORALL,
    LATEX_EXISTS,
    LATEX_TEXT,
    LATEX_SET,
    LATEX_ALIGN_ENV,
    MD_TABLE_HEADER_BODY,
    MD_TABLE_ALIGNMENT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LATEX_MATHBB:
        if (record->event.pressed) {
            SEND_STRING("\\mathbb{}");
        }
        break;

    case LATEX_FORALL:
        if (record->event.pressed) {
            SEND_STRING("\\forall");
        }
        break;

    case LATEX_EXISTS:
        if (record->event.pressed) {
           SEND_STRING("\\exists");
        }
        break;

    case LATEX_TEXT:
        if (record->event.pressed) {
           SEND_STRING("\\text{}");
        }
        break;
    
    case LATEX_SET:
        if (record->event.pressed) {
           SEND_STRING("\\{\\}");
        }
        break;

    case LATEX_ALIGN_ENV:
        if (record->event.pressed) {
            SEND_STRING("$$\\begin{align*}\\end{align*}$$");
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        KC_AUDIO_VOL_DOWN,    KC_AUDIO_VOL_UP,    KC_AUDIO_MUTE,
        KC_GRAVE,    KC_LEFT_ALT,    KC_TAB,
        LCTL(KC_C),    LCTL(KC_V),    KC_PRINT_SCREEN
    )
};
