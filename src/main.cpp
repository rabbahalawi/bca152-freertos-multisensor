#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Task handles
TaskHandle_t tempTaskHandle = NULL;
TaskHandle_t pressureTaskHandle = NULL;
TaskHandle_t systemTaskHandle = NULL;

// Task 1: Simulated Temperature & Humidity Sensor (Runs every 2s)
void vTemperatureTask(void *pvParameters) {
    while (1) {
        printf("[TEMP SENSOR] Temp: 26.4 C | Humidity: 58%%\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 2: Simulated Pressure Sensor (Runs every 3s)
void vPressureTask(void *pvParameters) {
    while (1) {
        printf("[PRESSURE SENSOR] Barometric Pressure: 1013.25 hPa\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// Task 3: System Health Monitor (Runs every 6s)
void vSystemStatusTask(void *pvParameters) {
    while (1) {
        printf("[SYSTEM MONITOR] Status: OK | Heap Free: Good\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}

extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(100)); // Short delay for driver readiness
    printf("\n========================================\n");
    printf("  BCA152 FreeRTOS Multisensor Active   \n");
    printf("========================================\n");
    fflush(stdout);

    // Spawn tasks with explicit priorities
    xTaskCreate(vTemperatureTask, "TempTask", 2048, NULL, 2, &tempTaskHandle);
    xTaskCreate(vPressureTask, "PressureTask", 2048, NULL, 2, &pressureTaskHandle);
    xTaskCreate(vSystemStatusTask, "SystemTask", 2048, NULL, 1, &systemTaskHandle);
}