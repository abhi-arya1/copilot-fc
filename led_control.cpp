#include "led_control.h"

void blink(int COLOR, int TIMES, int DELAY) {
  for(int i = 1; i <= TIMES; i++) {
    digitalWrite(COLOR, HIGH);
    delay(DELAY);
    digitalWrite(COLOR, LOW);
    delay(DELAY);
  }
}

void redOn() {
  digitalWrite(RED, HIGH);
}

void redOff() {
  digitalWrite(RED, LOW);
}

void blueOn() {
  digitalWrite(BLUE, HIGH);
}

void blueOff() {
  digitalWrite(BLUE, LOW);
}

void greenOn() {
  digitalWrite(GREEN, HIGH);
}

void greenOff() {
  digitalWrite(GREEN, LOW);
}

void pinkOn() {
  redOn(); blueOn();
}

void pinkOff() {
  redOff(); blueOff(); 
}

void cyanOn() {
  greenOn(); blueOn();
}

void cyanOff() {
  greenOff(); blueOff(); 
}

void yellowOn() {
  greenOn(); redOn();
}

void yellowOff() {
  greenOff(); redOff(); 
}
