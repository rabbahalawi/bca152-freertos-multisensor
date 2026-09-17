#ifndef ALARM_H
#define ALARM_H

// Thresholds for testing (adjust if your lab specified different numbers)
#define TEMP_THRESHOLD_LOW  18.0f
#define TEMP_THRESHOLD_HIGH 30.0f

enum class AlarmState { 
    NORMAL, 
    LOW_TEMPERATURE, 
    HIGH_TEMPERATURE 
}; 

AlarmState evaluateTemperature(float temperature); 

// NEW Part X: Declare the Alarm Task so main.cpp can use it
void vAlarmTask(void *pvParameters);

#endif // ALARM_H