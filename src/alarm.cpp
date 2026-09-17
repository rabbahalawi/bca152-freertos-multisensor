#include "alarm.h"

AlarmState evaluateTemperature(float temperature) {
    if (temperature < TEMP_THRESHOLD_LOW) {
        return AlarmState::LOW_TEMPERATURE;
    }
    if (temperature > TEMP_THRESHOLD_HIGH) {
        return AlarmState::HIGH_TEMPERATURE;
    }
    return AlarmState::NORMAL;
}