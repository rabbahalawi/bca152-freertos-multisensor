#include "system_state.h"

// Task 32: Initial system state defaults to ACTIVE
volatile SystemState g_systemState = SystemState::ACTIVE;

DisplayMode getNextDisplayMode(DisplayMode current) {
    switch (current) {
        case DisplayMode::TEMPERATURE: return DisplayMode::HUMIDITY;
        case DisplayMode::HUMIDITY:    return DisplayMode::LIGHT;
        case DisplayMode::LIGHT:       return DisplayMode::MOTION;
        case DisplayMode::MOTION:      return DisplayMode::TEMPERATURE;
    }
    return DisplayMode::TEMPERATURE;
}

DisplayMode getPreviousDisplayMode(DisplayMode current) {
    switch (current) {
        case DisplayMode::TEMPERATURE: return DisplayMode::MOTION;
        case DisplayMode::HUMIDITY:    return DisplayMode::TEMPERATURE;
        case DisplayMode::LIGHT:       return DisplayMode::HUMIDITY;
        case DisplayMode::MOTION:      return DisplayMode::LIGHT;
    }
    return DisplayMode::TEMPERATURE;
}