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

KALMAN altitudeFilter(1, 1, 0.04); 
MVAVG altFilter(5); 

// sensor information (IMU)
#define GYRO_DATA_RATE_HZ 100
#define GYRO_DR_DIVISOR 10
#define ACCEL_DATA_RATE_HZ 53.57
#define ACCEL_DR_DIVISOR 20

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
  baro.setMode(MPL3115A2_ALTIMETER);
  baro.setSeaPressure(BARO_ZERO_PRESSURE);
  altFilter.begin(); 
  print("Altimeter setup complete!");

  // ICM_20948X
  if (!icm.begin_I2C()) { 
    if (!icm.begin_I2C(0x69)) { // If not via default, try using I2C address 0x69
      print("Failed to find IMU");
      while (1);
    }}
  // TODO get IMU sensors calibrated with proper data ranges (FINISH THIS FIRST) 
  icm.setAccelRange(ICM20948_ACCEL_RANGE_16_G);
  icm.setGyroRange(ICM20948_GYRO_RANGE_2000_DPS);
  icm.setMagDataRate(AK09916_MAG_DATARATE_100_HZ);
  print("IMU setup and calibration complete!");


  // Setup Pyros ---------------
  if(COMP_MODE != 0) {
    pinMode(PYRO_CHUTE, OUTPUT); 
    print("Computer is: 'ARMED' on chute pyro channel."); 
    if(PYRO_CHUTE_BACKUP_EN) {
      pinMode(PYRO_CHUTE_BACKUP, OUTPUT); 
      print("Computer is: 'ARMED' on chute backup pyro channel."); 
    }
    print("Pyro Channel(s) Set Up");
  } else {
    print("COMP_MODE = 0: Computer is 'DISARMED' on all Pyro Channels");
  }

  // Setup Cooldown Sequence ---------------
  delay(750);
  redOff();
  print("Setup Complete");
  print("----------------------------");
  blink(GREEN, 3, 250); 
  delay(250); 

    // Ready for flight! ---------------
  flightMode = IDLE; 
  print("TAM is ready for flight. Flight Mode set to *IDLE* (0)");
}

void loop() {
  //float time = millis()/1000.0; // (for datalogging)
  //Serial.print("Flight Mode: "); Serial.println(flightMode); // (for testing)

  // TODO complete pyro test section (E-match units/transistors and power delivery)
  // if(COMP_MODE == 1) {
    
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
        
      // detect a potential launch 
      if(LAUNCH_METHOD == 0) 
      {
        // (TODO combine launch detect algo with accelerometer)
        float altitude = baro.getAltitude();
        float adjAltitude = altFilter.reading(altitude); 
        Serial.print(adjAltitude); Serial.print(", "); Serial.print(altitude); Serial.print(", "); Serial.println(initialAltitude); 

        // set a baseline altitude
        if (launchCheckZero <= 5) { 
          initialAltitude = altitude; 
          launchCheckZero++; 
        }

        // detect a launch (TODO combine with accelerometer data for accurancy)
        if ((adjAltitude - 1) > initialAltitude) { 
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
      yellowOn(); 

      // TODO data-logging and other ascent related features 
      
      break; 
    case DESCENT_RECOVERY: 
      blueOn(); 

      if(/*condition to fire pyro channels is*/ true && COMP_MODE != 0){
        // TODO add pyro support with power and transistors 
      }

      break;
    case LANDED: 
      greenOn(); 
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

    // TODO add this additional data and process it :)
    // rollRate = (float)gyro.gyro.x/16.4;
    // pitchRate = (float)gyro.gyro.y/16.4;

    // accelX = (float)accel.acceleration.x/2048;
    // accelY = (float)accel.acceleration.y/2048;
    // accelZ = (float)accel.acceleration.z/2048;

    // rollAngle = atan(accelY/sqrt(accelX*accelX + accelZ*accelZ)) * (1/(3.142/180)) + 1.67;
    // pitchAngle =  atan(accelZ/sqrt(accelY*accelY + accelX*accelX)) * (1/(3.142/180)); 

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

