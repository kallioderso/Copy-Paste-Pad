// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "raw_hid.h"
#include QMK_KEYBOARD_H

bool copy = false;
bool paste = false;


//  creates custom keycodes, to prevent interfering into
//  normal computer processes.

enum custom_keycodes {
    CP1 = QK_USER,
    CP2,
    CP3,
    CP4,
    CP5,
    CP6,
    CCM,
    PCM
};


//  defining the entire layout of the Copy-Paste-Pad
//  the graph below displays the layout in a pretty good way would i say
//  shoutout to the preshown graph, i never would have come to such a brilliant idea

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


//  creates hid events (hid stands for Human Interface Device and 
//  allows the communikation with the Computer itself, its mission 
//  is to copy and paste inside a different application in form of an .exe)

void create_hid(uint8_t id) { 
    uint8_t buffer[32] = {id};
    raw_hid_send(buffer, sizeof(buffer));
}

void update_oled(void);

//  creates custom interactions on the custom keys.
//  here we refer to the create_hid method to create hids, that the Computer-Application
//  than uses to copy and paste different things into the right positions

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(!record->event.pressed)
        return false;

    switch (keycode) {
        case CCM:
            if(!copy){
                copy = true;
                update_oled();
            }
            else{
                copy = false;
                update_oled();
            }
                
            return false;
        
        case PCM:
            if(!paste){
                paste = true;
                update_oled();
            }
            else{
                paste = false;
                update_oled();
            }

            return false;

        case CP1:
            if(copy)
                create_hid(1);
            else if(paste)
                create_hid(11);
            else
                create_hid(21);
            return false;

        case CP2:
            if(copy)
                create_hid(2);
            else if(paste)
                create_hid(12);
            else
                create_hid(22);
            return false;

        case CP3:
            if(copy)
                create_hid(3);
            else if(paste)
                create_hid(13);
            else
                create_hid(23);
            return false;

        case CP4:
            if(copy)
                create_hid(4);
            else if(paste)
                create_hid(14);
            else
                create_hid(24);
            return false;

        case CP5:
            if(copy)
                create_hid(5);
            else if(paste)
                create_hid(15);
            else
                create_hid(25);
            return false;

        case CP6:
            if(copy)
                create_hid(6);
            else if(paste)
                create_hid(16);
            else
                create_hid(26);
            return false;

        default:
            return true;
  }
}

//  this definition makes sure that the pins arent loaded, 
//  when no oled is activated to prevent errors

#ifdef OLED_ENABLE

//  method to display the current states of the oled screen
//  later the display of filled or non filled copy paste switches will be readed

void update_oled(void) {
    oled_clear();

    if(copy)
        oled_write_ln_P(PSTR("Copy"), false);
    else if(paste)
        oled_write_ln_P(PSTR("Paste"), false);
    else
        oled_write_ln_P(PSTR(">> Copy-Paste-Board <<"), false);
}

// void update_oled_clipboards(bool isFilled)
// {
//     oled_clear();

//     if(isFilled)
//         oled_write_ln_P(PSTR("filled"), false);
//     else
//         oled_write_ln_P(PSTR("empty"), false);

//     sleep(1);

//     update_oled();
// }

#endif