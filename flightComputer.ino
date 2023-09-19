#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPL3115A2.h>
#include <SD.h>
#include <SPI.h>

#include "commons.h"
#include "launch_config.h"

Adafruit_MPL3115A2 baro;
Adafruit_ICM20948 icm;

File altitude_and_pressure;
File speed_and_accel;
File gyro_angles;
File temps;
File gen_log; 

int flightMode; 
float launchCheckZero = 0;
float initialAltitude = 0; 

void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("Setup Begin");

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT); 

  redOn();

  if (!baro.begin()) {
    Serial.println("Altimeter Not Found");
    while(1);
  }
  Serial.println("Altimeter Initialized");
  baro.setSeaPressure(BARO_ZERO_PRESSURE);

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

  flightMode = 0; 

  delay(250); 
}

void loop() {
  //float time = millis()/1000.0;

  // if(COMP_MODE == 1) {
  //   // TODO complete pyro test section 
  // } 

  switch (flightMode) {
    case 0: /** IDLE */
      cyanOn();
      if(digitalRead(8) == HIGH) {
        flightMode = 1; 
        cyanOff(); 
      }
      break; 
    case 1: /** PAD */ 
    { pinkOn(); 
      
      if(LAUNCH_METHOD == 0) 
      { // detect a potential launch 
        // (TODO combine launch detect algo with accelerometer)
        float altitude = KALMAN_Altitude(baro.getAltitude());
        if (launchCheckZero == 0) { initialAltitude = baro.getAltitude(); launchCheckZero = 1; }
        Serial.print(altitude); Serial.print(", "); Serial.println(initialAltitude); 
        if ((altitude - 1) > initialAltitude) { flightMode = 2; pinkOff(); } // launch detected
      }
      else if (LAUNCH_METHOD == 1) {
        // TODO create self-launch pyro support  
      }

      break; 
    }
    case 2: /** LAUNCH */
      blueOn();  
      break;
    case 3: /** DETECTED APOGEE -> ENABLE RECOVERY */
      break;
    case 4: /** LANDED ROCKET */
      break;
    case 5: /** RECOVERY SUCCESSFUL */ 
      break; 
  }
}

