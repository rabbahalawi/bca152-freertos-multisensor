#ifndef ALARM_H
#define ALARM_H

constexpr float TEMP_THRESHOLD_LOW  = 18.0f;
constexpr float TEMP_THRESHOLD_HIGH = 30.0f;

enum class AlarmState { 
    NORMAL, 
    LOW_TEMPERATURE, 
    HIGH_TEMPERATURE 
}; 

AlarmState evaluateTemperature(float temperature);

#endif // ALARM_H