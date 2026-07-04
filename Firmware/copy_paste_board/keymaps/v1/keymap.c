// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool copy = false;
bool paste = false;

enum custom_keycodes {
    CP1 = SAFE_RANGE,
    CP2 = SAFE_RANGE,
    CP3 = SAFE_RANGE,
    CP4 = SAFE_RANGE,
    CP5 = SAFE_RANGE,
    CP6 = SAFE_RANGE,
    CCM = SAFE_RANGE,
    PCM = SAFE_RANGE
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ 1 │ 2 │ 3 │
     * ├───┼───┼───┼
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┼
     * │ C │   │ P │
     * └───┘   └───┘
     */
    [0] = LAYOUT(
        CP1,   CP2,   CP3,
        CP4,   CP5,   CP6,
        CCM,          PCM
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CCM:
        if(record->event.pressed){
            if(!Copying){
                Copying = true;
                update_oled();
            }
            else{
                Copying = false;
                update_oled();
            }
            
        }
        else{
        }
        return false;
    
    case PCM:
        if(record->event.pressed){
            if(!Pasting){
                Pasting = true;
                update_oled();
            }
            else{
                Pasting = false;
                update_oled();
            }
        }
        else{
        }
        return false;

    default:
        return true;
  }
}

#ifdef OLED_ENABLE

void update_oled() {
    oled_clear();

    if(Copying && Pasting)
        oled_write_ln_P(PSTR("Copy + Paste"), false);
    else if(Copying)
        oled_write_ln_P(PSTR("Copy"), false);
    else if(Pasting)
        oled_write_ln_P(PSTR("Paste"), false);
}

#endif

