#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// Step 24: Define Sensor Data exactly as specified
struct SensorData {
    float temperature;
    float humidity;
    int lightLevel;
    bool motionDetected;
};

// Step 25: Create Queues for Consumers
QueueHandle_t displayQueue = NULL;
QueueHandle_t alarmQueue = NULL;

// Producer Task (SensorTask)
void vSensorTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(2000); 

    struct SensorData data;

    while (1) {
        // Simulate sensor readings
        data.temperature = 25.40f;
        data.humidity = 61.20f;
        data.lightLevel = 85; 
        data.motionDetected = true; // Simulating motion trigger

        // Send data to both consumer queues
        xQueueSend(displayQueue, &data, portMAX_DELAY);
        xQueueSend(alarmQueue, &data, portMAX_DELAY);

        // Maintain strict periodic execution (Part IV requirement carried over)
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// Consumer 1 (DisplayTask)
void vDisplayTask(void *pvParameters) {
    struct SensorData rxData;
    while (1) {
        if (xQueueReceive(displayQueue, &rxData, portMAX_DELAY) == pdTRUE) {
            printf("[DISPLAY] Temp: %.2f C | Hum: %.2f %% | Light: %d | Motion: %s\n",
                   rxData.temperature, rxData.humidity, rxData.lightLevel,
                   rxData.motionDetected ? "YES" : "NO");
            fflush(stdout);
        }
    }
}

// Consumer 2 (AlarmTask)
void vAlarmTask(void *pvParameters) {
    struct SensorData rxData;
    while (1) {
        if (xQueueReceive(alarmQueue, &rxData, portMAX_DELAY) == pdTRUE) {
            // Trigger alarm logic based on data
            if (rxData.motionDetected) {
                printf(">> [ALARM] Motion detected! Security alert!\n");
            }
            if (rxData.temperature > 35.0f) {
                printf(">> [ALARM] High temperature warning!\n");
            }
            fflush(stdout);
        }
    }
}

extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(100));
    printf("\n--- Part V Data Communication Active ---\n");
    fflush(stdout);

    // Initialize queues (Capacity of 10 items each)
    displayQueue = xQueueCreate(10, sizeof(struct SensorData));
    alarmQueue = xQueueCreate(10, sizeof(struct SensorData));

    if (displayQueue != NULL && alarmQueue != NULL) {
        // Spawn tasks
        xTaskCreate(vSensorTask, "SensorTask", 2048, NULL, 2, NULL);
        xTaskCreate(vDisplayTask, "DisplayTask", 2048, NULL, 1, NULL);
        xTaskCreate(vAlarmTask, "AlarmTask", 2048, NULL, 1, NULL);
    }
}