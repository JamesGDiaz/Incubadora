#include "Arduino.h"
#include "Control.h"

#include <PID_v1.h>

//Define Variables we'll be connecting to
double SetPoint, Input, hotOutput, coldOutput;
//Specify the links and initial tuning parameters
double Kp=30, Ki=5, Kd=4;
PID hotPID(&Input, &hotOutput, &SetPoint, Kp, Ki, Kd, DIRECT);
PID coldPID(&Input, &coldOutput, &SetPoint, Kp, Ki, Kd, DIRECT);
int WindowSize = 3000;
unsigned long windowStartTime;

void setupControl(double* Sp)
{
    pinMode(RELAY_0, OUTPUT);
    pinMode(RELAY_1, OUTPUT);

    windowStartTime = millis();

    SetPoint = *Sp;

    //tell the PID to range between 0 and the full window size
    hotPID.SetOutputLimits(0, WindowSize);
    coldPID.SetOutputLimits(0, WindowSize);

    //turn the PID on
    hotPID.SetMode(AUTOMATIC);
    coldPID.SetMode(AUTOMATIC);
}

void loopControl(float* value){
    Input = *value;
    hotPID.Compute();
    coldPID.Compute();

    /************************************************
     turn the output pin on/off based on pid output
    ************************************************/
    unsigned long now = millis();
    if (now - windowStartTime > WindowSize)
    { //time to shift the Relay Window
        windowStartTime += WindowSize;
    }
    if (hotOutput > now - windowStartTime) digitalWrite(RELAY_1, HIGH);
    else digitalWrite(RELAY_1, LOW);
    if (coldOutput < now - windowStartTime) digitalWrite(RELAY_0, HIGH);
    else digitalWrite(RELAY_0, LOW);
}

void relayControl(int relay, char ON)
{
    if (ON)
    {
        digitalWrite(relay, HIGH);
    }
    else
    {
        digitalWrite(relay, LOW);
    }
}
