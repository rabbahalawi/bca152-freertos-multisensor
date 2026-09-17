#include "alarm.h"
#include "rtos_objects.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include <stdio.h> 

AlarmState evaluateTemperature(float temperature) {
    if (temperature < TEMP_THRESHOLD_LOW) {
        return AlarmState::LOW_TEMPERATURE;
    }
    if (temperature > TEMP_THRESHOLD_HIGH) {
        return AlarmState::HIGH_TEMPERATURE;
    }
    return AlarmState::NORMAL;
}

void vAlarmTask(void *pvParameters) {
    while (1) {
        EventBits_t uxBits = xEventGroupWaitBits(
            g_systemEvents, 
            EVENT_ALARM, 
            pdFALSE, 
            pdFALSE, 
            portMAX_DELAY 
        );

        if ((uxBits & EVENT_ALARM) != 0) {
            // NEW Part XI: Protect the Serial output with the Mutex
            if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
                printf(">>> WARNING: Temperature Threshold Alarm Active! <<<\n");
                xSemaphoreGive(serialMutex);
            }
            
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}