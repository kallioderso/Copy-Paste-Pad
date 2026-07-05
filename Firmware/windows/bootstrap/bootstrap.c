#include <windows.h>
#include <shlobj.h>
#include <objbase.h>
#include <stdio.h>

EXTERN_C const CLSID CLSID_ShellLink =
    {0x00021401,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

EXTERN_C const IID IID_IShellLinkA =
    {0x000214EE,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

EXTERN_C const IID IID_IPersistFile =
    {0x0000010b,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};


//  this method is there to take the CopyPasteBoard.exe file and put it
//  into autostart, so the keyboard will work each time after starting your PC
//  without the need of manualy clicking the .exe
//  this file was as well ai generated, as i had almost no more time left to my self set
//  deadline. but will be rewritten and improved in the future as well.
//  PS: "is spend to much time to perfectionize my Casing :P"

int main(void) {
    char appdata[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdata);

    char targetDir[MAX_PATH];
    sprintf(targetDir, "%s\\CopyPasteBoard", appdata);
    CreateDirectory(targetDir, NULL);

    char targetExe[MAX_PATH];
    sprintf(targetExe, "%s\\CopyPasteBoard.exe", targetDir);

    CopyFile("CopyPasteBoard.exe", targetExe, FALSE);

    char startup[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, 0, startup);

    char shortcutPath[MAX_PATH];
    sprintf(shortcutPath, "%s\\CopyPasteBoard.lnk", startup);

    CoInitialize(NULL);

    IShellLinkA* link;
    if (SUCCEEDED(CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                                   &IID_IShellLinkA, (LPVOID*)&link))) {

        link->lpVtbl->SetPath(link, targetExe);
        link->lpVtbl->SetDescription(link, "CopyPasteBoard");

        IPersistFile* file;
        if (SUCCEEDED(link->lpVtbl->QueryInterface(link, &IID_IPersistFile, (void**)&file))) {
            WCHAR wpath[MAX_PATH];
            MultiByteToWideChar(CP_ACP, 0, shortcutPath, -1, wpath, MAX_PATH);
            file->lpVtbl->Save(file, wpath, TRUE);
            file->lpVtbl->Release(file);
        }

        link->lpVtbl->Release(link);
    }

    CoUninitialize();

    ShellExecute(NULL, "open", targetExe, NULL, NULL, SW_HIDE);

    return 0;
}
