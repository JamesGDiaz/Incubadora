#ifndef _CONTROL
    #define _CONTROL

    #define PIN_SENSOR 0
    #define RELAY_0 8
    #define RELAY_1 9
    
    void setupControl(double*);
    void loopControl(float *);
    void relayControl(int relay, char status);
#endif
