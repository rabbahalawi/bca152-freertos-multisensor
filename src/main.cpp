#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

// Telemetry structure holding all Part IV sensor readings
typedef struct {
    float temperature;
    float humidity;
    float light_percent;
} sensor_telemetry_t;

QueueHandle_t sensorQueue = NULL;

// Step 22: SensorTask using vTaskDelayUntil to prevent timing drift
void vSensorTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(2000); // Strict 2000ms periodic cycle

    sensor_telemetry_t data;

    while (1) {
        // Step 20: DHT22 Simulated Values
        data.temperature = 25.40f;
        data.humidity = 61.20f;

        // Step 21: Simulated LDR ADC representation (0 - 100%)
        data.light_percent = 78.5f; 

        // Send combined telemetry to queue
        xQueueSend(sensorQueue, &data, portMAX_DELAY);

        // Guarantees execution at exactly fixed intervals regardless of task work duration
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// Telemetry Display Task
void vTelemetryTask(void *pvParameters) {
    sensor_telemetry_t rxData;
    while (1) {
        if (xQueueReceive(sensorQueue, &rxData, portMAX_DELAY) == pdTRUE) {
            printf("[SENSOR DATA] Temperature: %.2f C | Humidity: %.2f %% | Light: %.1f %%\n",
                   rxData.temperature, rxData.humidity, rxData.light_percent);
            fflush(stdout);
        }
    }
}

extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(100));
    printf("\n--- Part IV Sensor Subsystem Active ---\n");
    fflush(stdout);

    sensorQueue = xQueueCreate(10, sizeof(sensor_telemetry_t));

    if (sensorQueue != NULL) {
        xTaskCreate(vSensorTask, "SensorTask", 2048, NULL, 2, NULL);
        xTaskCreate(vTelemetryTask, "TelemetryTask", 2048, NULL, 1, NULL);
    }
}