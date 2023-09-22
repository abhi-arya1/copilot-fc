#ifndef FILTERS_H
#define FILTERS_H

#include <Arduino.h>

class KALMAN {
  public: 
    KALMAN(float measure_error, float est_error, float Q);
    float updateEstimate(float measured); 
    void setEstimateError(float est_error);
    void setMeasurementError(float measure_error);
    void setProcessNoise(float Q);

    float getKalmanGain();
    float getEstimateError();

  private:
    float _mes_err;
    float _est_err;
    float _Q;
    float _curr_est = 0;
    float _last_est = 0; 
    float _kalman_gain = 0;
};

// TODO tune Moving Average "READING" function 
class MVAVG {
  public:
    MVAVG(int interval)
        : m_interval{interval}, m_nbrReadings{0}, m_sum{0}, m_next{0} {}
    void begin();
    float reading(float newReading);
    void reset();

  private:
    int m_interval;     // number of data points for the moving average
    int m_nbrReadings;  // number of readings
    long m_sum;         // sum of the m_readings array
    int m_next;         // index to the next reading
    int* m_readings;    // pointer to the dynamically allocated interval array
};

#endif
