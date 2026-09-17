#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "freertos/FreeRTOS.h"

// Task 32: System State Machine Enums
enum class SystemState {
    ACTIVE,
    INACTIVE
};

// Task 28: Navigation Enums
enum class DisplayMode {
    TEMPERATURE,
    HUMIDITY,
    LIGHT,
    MOTION
};

enum class NavDirection {
    NEXT,
    PREVIOUS
};

// Global volatile state variable
extern volatile SystemState g_systemState;

// Navigation function prototypes
DisplayMode getNextDisplayMode(DisplayMode current);
DisplayMode getPreviousDisplayMode(DisplayMode current);

#endif // SYSTEM_STATE_H