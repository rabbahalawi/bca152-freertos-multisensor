#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Task handles
TaskHandle_t tempTaskHandle = NULL;
TaskHandle_t systemTaskHandle = NULL;

// Task 1: Simulates reading a temperature sensor every 2 seconds
void vTemperatureTask(void *pvParameters) {
    while (1) {
        printf("[TEMP SENSOR] Reading temperature: 25.5 C\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 2: Prints system health status every 5 seconds
void vSystemStatusTask(void *pvParameters) {
    while (1) {
        printf("[SYSTEM] Status: ALL SYSTEMS OPERATIONAL\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

extern "C" void app_main(void) {
    printf("\n--- BCA152 FreeRTOS Multisensor Starting ---\n");
    fflush(stdout);

    // Create FreeRTOS Tasks
    xTaskCreate(
        vTemperatureTask,     // Task function
        "TempTask",           // Name for debugging
        2048,                 // Stack size in words
        NULL,                 // Task input parameter
        2,                    // Task priority
        &tempTaskHandle       // Task handle
    );

    xTaskCreate(
        vSystemStatusTask,
        "SystemTask",
        2048,
        NULL,
        1,                    // Lower priority
        &systemTaskHandle
    );
}