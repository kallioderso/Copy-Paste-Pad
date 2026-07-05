#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "clipboard.h"


//  method that first does "strg" + "c" and than opens the clipboard
//  to steal the data from it xD. than the data gets copyied into pointers and copyied
//  in general, so that it wouldnt get lost on its way towards the storing location

char* copyText(void) {
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event('C', 0, 0, 0);
    keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

    OpenClipboard(NULL);
    HANDLE HandleData = GetClipboardData(CF_TEXT);
    if(!HandleData) {
        CloseClipboard();
        return NULL;
    }

    char *textcopy = GlobalLock(HandleData);
    char *text = _strdup(textcopy);

    GlobalUnlock(HandleData);
    CloseClipboard();

    return text;
}


//  this method does the completly opposit of the method before
//  it gets the stored texts as input and than obviously checks if they are empty
//  to reduce unneccesary opperations. than it prereservates the necessary RAM memory
//  both for global memory and clipboard memory and prepares the data for the transfer
//  followed by the transfer and the usage of "strg" + "v" to paste everything

void pasteText(const char* text) {
    if(text == NULL)
        return;

    OpenClipboard(NULL);
    EmptyClipboard();

    size_t length = strlen(text);
    HGLOBAL HeapMemory = GlobalAlloc(GMEM_MOVEABLE, length);

    memcpy(GlobalLock(HeapMemory), text, length);
    GlobalUnlock(HeapMemory);

    SetClipboardData(CF_TEXT, HeapMemory);

    CloseClipboard();

    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}