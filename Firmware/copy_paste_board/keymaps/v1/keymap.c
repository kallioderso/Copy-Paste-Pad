// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool copy = false;
bool paste = false;

enum custom_keycodes {
    CP1 = QK_USER,
    CP2,
    CP3,
    CP4,
    CP5,
    CP6,
    CCM,
    PCM
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
            if(!copy){
                copy = true;
                update_oled();
            }
            else{
                copy = false;
                update_oled();
            }
            
        }
        else{
        }
        return false;
    
    case PCM:
        if(record->event.pressed){
            if(!paste){
                paste = true;
                update_oled();
            }
            else{
                paste = false;
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

    if(copy && paste)
        oled_write_ln_P(PSTR("Copy + Paste"), false);
    else if(copy)
        oled_write_ln_P(PSTR("Copy"), false);
    else if(paste)
        oled_write_ln_P(PSTR("Paste"), false);
}

#endif