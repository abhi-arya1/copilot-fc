#ifndef KALMAN_H
#define KALMAN_H

#include <Arduino.h>

// U being the noisy measurement, and U_hat being the filtered estimate 
float KALMAN_Altitude(float U);

#endif
