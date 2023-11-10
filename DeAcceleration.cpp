#include <iostream>
#include "windows.h"
using std::cout;
using std::endl;
using std::string;
// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfow

string RegistryString(const int pvParam[3]){
    string reg;
    reg = "MouseSpeed: " + std::to_string(pvParam[2]) + '\n';
    reg += "MouseThreshold1: " + std::to_string(pvParam[0]) + '\n';
    reg += "MouseThreshold2: " + std::to_string(pvParam[1]) + '\n';
    return reg;
}

void disableMouseAccel(){

    
}

int main(){
    // BOOL SystemParametersInfoW(
    // [in]      UINT  uiAction,
    // [in]      UINT  uiParam,
    // [in, out] PVOID pvParam,
    // [in]      UINT  fWinIni
    // );

    // Retrieves the two mouse threshold values and the mouse acceleration. 
    // The pvParam parameter must point to an array of three integers that receives these values.
    int pvParam[3]; 

    // Mouse Accel on: MT1 = 6, MT2 = 10, MouseSpeed = 1.
    SystemParametersInfoW(SPI_GETMOUSE, 0, pvParam, 0);

    cout << RegistryString(pvParam);
}
