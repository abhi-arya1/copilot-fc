#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPL3115A2.h>
#include <SD.h>
#include <SPI.h>

#include "commons.h"

Adafruit_MPL3115A2 baro;
Adafruit_ICM20948 icm;

void setup() {
  Serial.begin(9600);
  delay(3000);

  Serial.println("Setup Begin");

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  redOn();

  if (!baro.begin()) {
    Serial.println("Altimeter Not Found");
    while(1);
  }
  Serial.println("Altimeter Initialized");
  baro.setSeaPressure(1013.26);

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
  blink(GREEN, 4);
}

void loop() {
  // work in progress 
}
