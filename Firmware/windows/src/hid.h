#pragma once
#include <stdint.h>
#include <windows.h>

#define HID_BUFFER_SIZE 32

HANDLE hid_open(void);
int hid_read(HANDLE device, uint8_t* buffer);
void hid_close(HANDLE device);