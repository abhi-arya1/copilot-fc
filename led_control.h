#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

#define RED 6
#define GREEN 4 
#define BLUE 5 

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
