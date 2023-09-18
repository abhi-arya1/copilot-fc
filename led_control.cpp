#include "led_control.h"

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

void blink(int COLOR, int TIMES) {
  for(int i = 1; i <= TIMES; i++) {
    digitalWrite(COLOR, HIGH);
    delay(450);
    digitalWrite(COLOR, LOW);
    delay(450);
  }
}