#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// 1. Sensor Data Structure
typedef struct {
    char sensor_name[16];
    float value;
} sensor_data_t;

// 2. Global Queue Handle
QueueHandle_t sensorQueue = NULL;

// Task 1: Temperature Sensor Producer
void vTemperatureTask(void *pvParameters) {
    sensor_data_t data;
    strncpy(data.sensor_name, "TEMP", sizeof(data.sensor_name));
    
    while (1) {
        data.value = 26.5f; // Simulated temperature reading
        xQueueSend(sensorQueue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// Task 2: Pressure Sensor Producer
void vPressureTask(void *pvParameters) {
    sensor_data_t data;
    strncpy(data.sensor_name, "PRESSURE", sizeof(data.sensor_name));
    
    while (1) {
        data.value = 1013.25f; // Simulated pressure reading
        xQueueSend(sensorQueue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// Task 3: Central Telemetry Consumer (Receives data from queue)
void vTelemetryTask(void *pvParameters) {
    sensor_data_t receivedData;
    
    while (1) {
        // Wait indefinitely for data from any sensor task
        if (xQueueReceive(sensorQueue, &receivedData, portMAX_DELAY) == pdTRUE) {
            printf("[TELEMETRY QUEUE] Data from %s: %.2f\n", receivedData.sensor_name, receivedData.value);
            fflush(stdout);
        }
    }
}

extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(100));
    printf("\n--- BCA152 Queue Telemetry Active ---\n");
    fflush(stdout);

    // Create Queue to hold up to 10 sensor messages
    sensorQueue = xQueueCreate(10, sizeof(sensor_data_t));

    if (sensorQueue != NULL) {
        // Spawn Sensor Producer Tasks
        xTaskCreate(vTemperatureTask, "TempTask", 2048, NULL, 2, NULL);
        xTaskCreate(vPressureTask, "PressureTask", 2048, NULL, 2, NULL);
        
        // Spawn Telemetry Consumer Task
        xTaskCreate(vTelemetryTask, "TelemetryTask", 2048, NULL, 1, NULL);
    } else {
        printf("Failed to create sensorQueue!\n");
    }
}