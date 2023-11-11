// Copyright 2023 Ted Akahori
#include <iostream>
#include <Windows.h>
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

int pvParam[3];

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

void disableMouseAccel(){
    pvParam[0], pvParam[1], pvParam[2] = 0;
    // Seems to work to disable mouse acceleration, but doesn't change registry properly.
    SystemParametersInfoW(SPI_SETMOUSE, 0, pvParam, SPIF_SENDCHANGE);

}

int main(){
    if(AccelStatus()){
        disableMouseAccel();
    }
}