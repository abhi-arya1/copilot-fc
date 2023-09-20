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
File syLog; 

int flightMode = IDLE; 
float launchCheckZero = 0;
float initialAltitude = 0;
float maximumAltitude = 0;  

void sysLog(String s); 
void print(String s); 

void setup() {
  // Begin Serial Output --------------- 
  Serial.begin(BAUD_RATE);
  delay(3000); 

  // Initialize RGB Pins and Start-up LED ---------------
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT); 

  redOn();

  // Begin SD card for data logging ---------------
  if (!SD.begin(CS_PIN)) {
    print("SD card not inserted or card reader not found.");
    while (1);
  }
  print("SD found! Started logging now!");

  // begin logs ---------------
  print("----------------------------");
  print("Welcome to TAM (Software Version: pre-alpha v0.0.1)"); 
  String baud = "Setup Begin with Serial on BAUD_RATE: ";
  baud = baud + BAUD_RATE; 
  print(baud); 

  // Initialize Sensors ---------------

  // MPL3115A2
  if (!baro.begin()) {
    print("Altimeter Not Found");
    while(1);
  }
  print("Altimeter found!");
  baro.setMode(MPL3115A2_ALTIMETER);
  baro.setSeaPressure(BARO_ZERO_PRESSURE);

  // ICM_20948X
  if (!icm.begin_I2C()) { 
    if (!icm.begin_I2C(0x69)) { // If not via default, try using I2C address 0x69
      print("Failed to find IMU");
      while (1);
    }}
  print("IMU found!");
  // TODO get IMU sensors calibrated with proper data ranges 

  // Setup Cooldown Sequence ---------------
  delay(750);
  redOff();
  print("Setup Complete");
  print("----------------------------");
  blink(GREEN, 2, 300); 
  delay(250); 

    // Ready for flight! ---------------
  flightMode = IDLE; 
  print("TAM is ready for flight. Flight Mode set to *IDLE* (0)");
}

void loop() {
  //float time = millis()/1000.0; // (for datalogging)
  //Serial.print("Flight Mode: "); Serial.println(flightMode); // (for testing)

  // TODO complete pyro test section (E-match units)
  // if(COMP_MODE == 1) {
  //   
  // } 
  

  // Mode switcher ---------------
  switch (flightMode) {
    case IDLE: 
      cyanOn();
      if(digitalRead(8) == HIGH) { // check for button press to disable idle mode (to be replaced with screw switch)
        print("Flight Mode Changed to *PAD* (1) from *IDLE* (0)");
        flightMode = PAD; 
        cyanOff(); 
      }
      break; 
    case PAD: 
    { pinkOn(); 
        
      if(LAUNCH_METHOD == 0) 
      { // detect a potential launch 
        // (TODO combine launch detect algo with accelerometer)
        float altitude = KALMAN_Altitude(baro.getAltitude());
        Serial.print(altitude); Serial.print(", "); Serial.println(initialAltitude); 

        // set a baseline altitude
        if (launchCheckZero <= 5) { 
          initialAltitude = baro.getAltitude(); 
          launchCheckZero++; 
        }

        // detect a launch (TODO combine with accelerometer data for accurancy)
        if ((altitude - 1) > initialAltitude) { 
          flightMode = ASCENT; pinkOff(); 
          print("LAUNCH DETECTED, Flight Mode Changed to *ASCENT* (2) from *PAD* (1)");
        }
      }
      else if (LAUNCH_METHOD == 1) {
        // TODO create self-launch pyro support (coming soon) 
      }
      break; 
    } // TODO finish stage handling 
    case ASCENT:
      blueOn(); 

      // TODO data-logging and other ascent related features 
      
      break; 
    case DESCENT_RECOVERY: 
      // TODO parachute handling 
      break;
    case LANDED: 
      // TODO celebrate! (also make sure SD files are saved and the computer is yk...alive)
      break;
  }

  // Data Logger ---------------
  if(flightMode != IDLE && flightMode != PAD && flightMode != LANDED) {
    // IMU Data
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    icm.getEvent(&accel, &gyro, &temp); 

    // Altimeter Data 
    float altitude = baro.getAltitude();
    float pressure = baro.getPressure();

    // TODO complete data logger 
  }
}

void sysLog(String s) {
  syLog = SD.open("sysLog.txt", FILE_WRITE);
  if(syLog) {
    // print general log information before message 
    syLog.print("Time: "); syLog.print(millis()/1000.0); syLog.print(" / Flight Mode: ");
    syLog.print(flightMode); syLog.print(" / --> "); 

    syLog.println(s); 
    syLog.close();
  }
}

void print(String s) {
  Serial.print("Time: "); Serial.print(millis()/1000.0); Serial.print(" / FltMode: ");
  Serial.print(flightMode); Serial.print(" / --> "); 
  Serial.println(s);
  sysLog(s); 
}

