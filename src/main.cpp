#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(100));

    printf("\n- BCA152 FreeRTOS Multisensor -\n");
    printf("- System starting...\n");
    fflush(stdout);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}