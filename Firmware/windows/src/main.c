#include <stdio.h>
#include <stdint.h>
#include <windows.h>

#include "clipboard.h"
#include "hid.h"

//  these are the 6 different data storages, each for one of the keys

char* storage[6] = { NULL, NULL, NULL, NULL, NULL, NULL };


//  this method interprates the given hid ids towards the right opperation
//  1-6: copying
//  11-16: pasting
//  it uses the methods declared inside the clipboard.c file, accesing it with the clipboard.h file

void handle_event(uint8_t id) {
    if (id >= 1 && id <= 6) {
        char* text = copyText();
        if (text != NULL)
            storage[id - 1] = text;
        return;
    }

    if (id >= 11 && id <= 16) {
        int slot = id - 11;
        pasteText(storage[slot]);
        return;
    }
}


//  this is the core of the whole .exe application as second part of 
//  the firmware inside the keyboard. first it has to check if the keyboard
//  evenly is connected and if not than stop the opperation
//  if everythings working, the infite loop starts, declared by while (1)
//  there it always starts the handle_event() method from above with a 
// 10s delay beetwheen each new cicle

int main(void) {
    HANDLE device = hid_open();
    if (!device)
        return 1;

    uint8_t buffer[HID_BUFFER_SIZE];

    while (1) {
        int result = hid_read(device, buffer);
        if (result > 0) {
            uint8_t event = buffer[0];
            handle_event(event);
        }
        Sleep(10);
    }

    hid_close(device);
    return 0;
}
