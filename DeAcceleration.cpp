// Copyright 2023 Ted Akahori
#include <iostream>
#include <Windows.h>
#include "DeAcceleration.h"
using std::cout;
using std::endl;
using std::string;

/* 
winuser Docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfow
Uses input parameters SPI_GETMOUSE 0x0003 & SPI_SETMOUSE 0x0004.
BOOL SystemParametersInfoW(
[in]      UINT  uiAction,
[in]      UINT  uiParam,
[in, out] PVOID pvParam,
[in]      UINT  fWinIni
);

winreg Docs: https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regnotifychangekeyvalue
LSTATUS RegNotifyChangeKeyValue(
  [in]           HKEY   hKey,
  [in]           BOOL   bWatchSubtree,
  [in]           DWORD  dwNotifyFilter,
  [in, optional] HANDLE hEvent,
  [in]           BOOL   fAsynchronous
);
*/

// Used in SystemParametersInfoW
int pvParam[3];

// Used to edit registry values.
HKEY hKey;

bool AccelStatus(){
    // Mouse Accel on: [MT1 = 6, MT2 = 10, MouseSpeed = 1].
    SystemParametersInfoW(SPI_GETMOUSE, 0, pvParam, 0);
    if(pvParam[2] == 0) {
        return 0;
    } else {
        return 1;
    }
}

string RegistryString(const int pvParam[3]){
    string reg;
    reg = "MouseSpeed: " + std::to_string(pvParam[2]) + '\n';
    reg += "MouseThreshold1: " + std::to_string(pvParam[0]) + '\n';
    reg += "MouseThreshold2: " + std::to_string(pvParam[1]) + '\n';
    return reg;
}

bool ZeroAccelerationInRegistry(){
    WCHAR newVal[] = L"0";
    DWORD valLen = (lstrlenW(newVal) + 1) * sizeof(WCHAR);
    LONG result = RegSetValueEx(
        hKey,
        "MouseSpeed",
        0,
        REG_SZ,
        (LPBYTE)newVal,
        valLen
    );
    if(result != ERROR_SUCCESS){
        std::cerr << "Error setting registry key, exiting.";
        return false;
    }
    RegSetValueEx(
        hKey,
        "MouseThreshold1",
        0,
        REG_SZ,
        (LPBYTE)newVal,
        valLen
    );
    RegSetValueEx(
        hKey,
        "MouseThreshold2",
        0,
        REG_SZ,
        (LPBYTE)newVal,
        valLen
    );
    return true;
}

void DisableMouseAccel(){
    pvParam[0], pvParam[1], pvParam[2] = 0;
    // Seems to work to disable mouse acceleration, but doesn't change registry properly.
    SystemParametersInfoW(SPI_SETMOUSE, 0, pvParam, SPIF_SENDCHANGE);
    
    // Changes registry to reflect above changes.
    ZeroAccelerationInRegistry();

}

int main(){
    RegOpenKeyEx(
        HKEY_CURRENT_USER,
        "Control Panel\\Mouse",
        0,
        KEY_SET_VALUE,
        &hKey
    );

    if(AccelStatus()){
        DisableMouseAccel();
    }

    RegCloseKey(hKey);

    return 0;
}


// HKEY hKey;
//     // Open the Mouse Registry
//     LONG result = RegOpenKeyEx(
//         HKEY_CURRENT_USER,
//         "Control Panel\\Mouse",
//         0,
//         KEY_NOTIFY,
//         &hKey
//     );
//     if (result != ERROR_SUCCESS) {
//         std::cerr << "Error opening registry key: " << result << endl;
//         return 1;
//     }
//     // Create listening event
//     HANDLE hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
//     if (hEvent == nullptr) {
//         std::cerr << "Error creating event: " << GetLastError() << endl;
//         RegCloseKey(hKey);
//         return 1;
//     }

//     // A forever loop since this runs until it's closed.
//     while(true){
//         result = RegNotifyChangeKeyValue(
//             hKey,
//             TRUE,
//             REG_NOTIFY_CHANGE_LAST_SET,
//             hEvent,
//             TRUE
//         );
//         if (result != ERROR_SUCCESS) {
//             std::cerr << "Error creating registry change event" << endl;
//             break;
//         }

//         WaitForSingleObject(hEvent, INFINITE);
        
//         if(AccelStatus()){
//             disableMouseAccel();
//         }
//     }