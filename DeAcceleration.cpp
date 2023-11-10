#include <iostream>
#include "winuser.h"
using std::cout;
using std::endl;
using std::string;

// Winuser Docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfow
// Uses input parameter SPI_GETMOUSE 0x0003 & output parameter SPI_SETMOUSE 0x0004.
// BOOL SystemParametersInfoW(
// [in]      UINT  uiAction,
// [in]      UINT  uiParam,
// [in, out] PVOID pvParam,
// [in]      UINT  fWinIni
// );

int pvParam[3];


bool updateAccelStatus(){
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
    SystemParametersInfoW(SPI_SETMOUSE, 0, pvParam, SPIF_SENDCHANGE);
}

int main(){
    disableMouseAccel();

    cout << RegistryString();

}
