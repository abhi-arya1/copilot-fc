#ifndef KALMAN_H
#define KALMAN_H

#include <Arduino.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>

// U being the noisy measurement, and U_hat being the filtered estimate 
float KALMAN_Altitude(float U);

#endif