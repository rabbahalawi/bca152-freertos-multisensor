#include "display.h"
#include "system_state.h"
#include "input.h"
#include "sensors.h"
#include "rtos_objects.h"
#include "ssd1306.h"
#include <stdio.h>
#include <string.h>

void vDisplayTask(void *pvParameters) {
    SSD1306_t dev;
    i2c_master_init(&dev, GPIO_NUM_21, GPIO_NUM_22, GPIO_NUM_NC);
    ssd1306_init(&dev, 128, 64);
    ssd1306_clear_screen(&dev, false);

    DisplayMode currentMode = DisplayMode::TEMPERATURE;
    SensorData sensorData = {};
    NavDirection navDir;
    char buffer[20];

    while (1) {
        if (xQueueReceive(navQueue, &navDir, 0) == pdTRUE) {
            if (navDir == NavDirection::NEXT) {
                currentMode = nextDisplayMode(currentMode);
            } else if (navDir == NavDirection::PREVIOUS) {
                currentMode = previousDisplayMode(currentMode);
            }
        }

        xQueueReceive(displayQueue, &sensorData, 0);

        ssd1306_clear_screen(&dev, false);

        switch (currentMode) {
            case DisplayMode::TEMPERATURE:
                ssd1306_display_text(&dev, 0, "ROOM MONITOR", 12, false);
                ssd1306_display_text(&dev, 2, "Page: Temp", 10, false);
                snprintf(buffer, sizeof(buffer), "%.1f C", sensorData.temperature);
                ssd1306_display_text(&dev, 4, buffer, strlen(buffer), false);
                break;

            case DisplayMode::HUMIDITY:
                ssd1306_display_text(&dev, 0, "ROOM MONITOR", 12, false);
                ssd1306_display_text(&dev, 2, "Page: Humidity", 14, false);
                snprintf(buffer, sizeof(buffer), "%.1f %%", sensorData.humidity);
                ssd1306_display_text(&dev, 4, buffer, strlen(buffer), false);
                break;

            case DisplayMode::LIGHT:
                ssd1306_display_text(&dev, 0, "ROOM MONITOR", 12, false);
                ssd1306_display_text(&dev, 2, "Page: Light", 11, false);
                snprintf(buffer, sizeof(buffer), "%d %%", sensorData.lightLevel);
                ssd1306_display_text(&dev, 4, buffer, strlen(buffer), false);
                break;

            case DisplayMode::MOTION:
                ssd1306_display_text(&dev, 0, "ROOM MONITOR", 12, false);
                ssd1306_display_text(&dev, 2, "Page: Motion", 12, false);
                snprintf(buffer, sizeof(buffer), "%s", sensorData.motionDetected ? "DETECTED" : "CLEAR");
                ssd1306_display_text(&dev, 4, buffer, strlen(buffer), false);
                break;
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}