#include "Arduino.h"
#include "Display.h"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numRows = 2;
const int numCols = 16;

void setupLCD() {
  // set up the LCD's number of columns and rows:
  lcd.begin(numCols, numRows);
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.setCursor(0,1);
  lcd.print(String(char(0b11110010))+":");
  lcd.setCursor(13,0);
  lcd.print("Rf");
  lcd.setCursor(13,1);
  lcd.print("Rc");
}

void showSensorTemp(double T){
  lcd.setCursor(2,0);
  lcd.print(String(T,1)+char(0xDF)+"C");
}
void showSetpointTemp(double T){
  lcd.setCursor(2,1);
  lcd.print(String(T,1)+char(0xDF)+"C");
}
void showActivatedRelays(char r){
  int R1 = r & 0b01;
  int R2 = (r & 0b10) >> 1;
  lcd.setCursor(15,0);
  if(R1) {
    lcd.print(char(255));
  } else lcd.print(" ");
  lcd.setCursor(15,1);
  if(R2) {
    lcd.print(char(255));
  } else lcd.print(" ");
}
