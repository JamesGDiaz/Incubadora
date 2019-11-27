#include "Display.h"
#include "Control.h"

double Setpoint =36.5;

void display(float C)
{
  Serial.print(float(C));
  Serial.println(" C");
  showSensorTemp(float(C));
  char activeRelays = (digitalRead(RELAY_1) << 1) & digitalRead(RELAY_0);
  showActivatedRelays(activeRelays);
}

void firstStage()
{
  float val = analogRead(PIN_SENSOR);
  float C = val * 500 / 1024.0;
  while (C >= Setpoint + 1.5 || C <= Setpoint - 1.5)
  {
    val = analogRead(PIN_SENSOR);
    C = val * 500 / 1024.0;

    if (C > Setpoint + 1.5)
    {
      relayControl(RELAY_0, HIGH);
      relayControl(RELAY_1, LOW);
    }
    else if (C < Setpoint - 1.5)
    {
      relayControl(RELAY_0, LOW);
      relayControl(RELAY_1, HIGH);
    }
    display(C);
    delay(500);
  }
  relayControl(RELAY_0, LOW);
  relayControl(RELAY_0, LOW);
}

void setup()
{
  setupLCD();
  setupControl(&Setpoint);
  Serial.begin(57600);
  showSetpointTemp(Setpoint);

  firstStage();
  Serial.println("Finished first stage!");
}

int updateLCDtime = 250;
unsigned long prevTime = millis();

void loop()
{
  float val = analogRead(PIN_SENSOR);
  float C = val * 500 / 1024.0;

  loopControl(&C);

  unsigned long now = millis();
  if (now - prevTime >= updateLCDtime)
  {
    display(C);
    prevTime = now;
  }
}
