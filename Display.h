#include <LiquidCrystal.h>

#ifndef _DISPLAY
    #define _DISPLAY
    void setupLCD();
    void showSensorTemp(double T);
    void showSetpointTemp(double T);
    void showActivatedRelays(char r);
#endif