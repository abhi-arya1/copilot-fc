#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPL3115A2.h>
#include <SD.h>
#include <SPI.h>

#include "commons.h"

Adafruit_MPL3115A2 baro;
Adafruit_ICM20948 icm;

File altitude_and_pressure;
File speed_and_accel;
File gyro_angles;
File temps;
File gen_log; 

int flightMode; 

void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("Setup Begin");

  pinflightMode(5, OUTPUT);
  pinflightMode(6, OUTPUT);
  pinflightMode(7, OUTPUT);

  redOn();

  if (!baro.begin()) {
    Serial.println("Altimeter Not Found");
    while(1);
  }
  Serial.println("Altimeter Initialized");
  baro.setSeaPressure(1014.10);

  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card not inserted or card reader not found.");
    while (1);
  }
  Serial.println("SD found!");

  if (!icm.begin_I2C()) { 
    if (!icm.begin_I2C(0x69)) { // If not via default, try using I2C address 0x69
      Serial.println("Failed to find IMU");
      while (1);
    }}
  Serial.println("IMU Found!");

  delay(1500);
  redOff();

  Serial.println("Setup Complete");
  blink(GREEN, 2);

  flightMode = 1; 
}

void loop() {
  float time = millis()/1000.0;

  switch (flightMode) {
    case 0: /** IDLE */
      // if ready on pad, switch to PAD flightMode 
    case 1: /** PAD */
      // if(detect_launch()) { 
      //   flightMode = 2; 
      // } 
    case 2: /** LAUNCH */
      break;
    case 3: /** DETECTED APOGEE RECOVERY */
      break;
    case 4: /** LANDED ROCKET */
      break;
    case 5: /** RECOVERY SUCCESSFUL */ 
      break; 
  }
}

