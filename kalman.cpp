#include "kalman.h"

// TODO get a better Kalman Filter algo ASAP 
// tuned y/n: "mostly complete"
float KALMAN_Altitude(float U) {

  // constants 
  static const float R = 45; // noise covariance (higher = more filtering + more time)(10)
  static const float H = 1.00; // mes. map scalar
  static float Q = 10; // initial estimated covariance 
  static float P = 0; // inital error covariance (must be 0)
  static float U_hat = 0; // initial estimated state (assume unknown)
  static float K = 0; // initial Kalman gain 

  // the filter algo
  K = P*H/(H*P*H+R); // update kalman gain 
  U_hat = U_hat + K*(U-H*U_hat); // update estimated 
   
  // update error covariance 
  P = (1-K*H)*P + Q; 

  return U_hat; // return estimated
}
