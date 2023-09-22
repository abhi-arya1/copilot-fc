#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

#define RED 5
#define GREEN 6 
#define BLUE 7 

void blink(int COLOR, int TIMES, int DELAY);

void redOn();
void redOff();
void greenOn();
void greenOff();
void blueOn();
void blueOff();

void pinkOn();
void pinkOff(); 
void cyanOn();
void cyanOff(); 
void yellowOn();
void yellowOff(); 

#endif
