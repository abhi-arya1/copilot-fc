#include "filters.h"
#include <math.h>

// KALMAN FILTER ---------------------------------------------------
KALMAN::KALMAN(float measure_error, float est_error, float Q) {
  _mes_err = measure_error;
  _est_err = est_error; 
  _Q = Q;
}

float KALMAN::updateEstimate(float measured) {
  _kalman_gain = _est_err/(_est_err + _mes_err);
  _curr_est = _last_est + _kalman_gain * (measured - _last_est);
  _est_err = (1.0f - _kalman_gain) * _est_err + fabsf(_last_est - _curr_est)*_Q;
  _last_est = _curr_est;

  return _curr_est;
}

void KALMAN::setEstimateError(float est_error) {
  _est_err = est_error; 
}

void KALMAN::setMeasurementError(float measure_error) {
  _mes_err = measure_error;
}

void KALMAN::setProcessNoise(float Q) {
  _Q = Q;
}

float KALMAN::getKalmanGain() {
  return _kalman_gain;
}

float KALMAN::getEstimateError() {
  return _est_err; 
}

// MOVING AVERAGE FILTER -----------------------------------------------
void MVAVG::begin()
{
    m_readings = new int[m_interval];
}

// add a new reading and return the new moving average
float MVAVG::reading(float newReading)
{
    // add each new data point to the sum until the m_readings array is filled
    if (m_nbrReadings < m_interval) {
        ++m_nbrReadings;
        m_sum += newReading;
    }
    // once the array is filled, subtract the oldest data point and add the new one
    else {
        m_sum = m_sum - m_readings[m_next] + newReading;
    }

    m_readings[m_next] = newReading;
    if (++m_next >= m_interval) m_next = 0;
    return (m_sum + m_nbrReadings / 2.0) / ((float) m_nbrReadings);
}

// start the moving average over again
void MVAVG::reset()
{
    m_nbrReadings = 0;
    m_sum = 0;
    m_next = 0;
}

