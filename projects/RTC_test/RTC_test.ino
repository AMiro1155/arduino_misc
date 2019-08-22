#include "Wire.h"
#define rtc_address 0xDF 

byte number = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600); 
}


void loop() {
  delay(1000);

  Wire.beginTransmission(rtc_address);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(rtc_address,7);

  byte seconds = 0xFF;
  byte minutes = 0xFF;
  byte hours = 0xFF;
  byte day = 0xFF;
  byte date = 0xFF;
  byte month = 0xFF;
  byte year = 0xFF;
  
  if (Wire.available()) {
    seconds = (Wire.read() & 0x7F);
    minutes = (Wire.read() & 0x7F);
    hours = (Wire.read() & 0x1F);
    day = (Wire.read() & 0x07);
    date = (Wire.read() & 0x07);
    month = (Wire.read() & 0x07);
    year = (Wire.read() & 0x07);
  }

  if (Serial.available() >= 1) {
    char c = Serial.read();
    if (c == 's') { // Start the RTC
      Serial.println("Initialising");
      Wire.beginTransmission(rtc_address);
      Wire.write(0x00);
      Wire.write(0x80); 
      Wire.endTransmission();
    }
  }
}
