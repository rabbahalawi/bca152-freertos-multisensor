#include "alarm.h"
#include <stdio.h>

// Hide all hardware and RTOS headers from the native compiler
#ifndef UNIT_TEST
#include "rtos_objects.h"
#include "sensors.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define BUZZER_PIN GPIO_NUM_14
#define BUZZER_LEDC_TIMER      LEDC_TIMER_0
#define BUZZER_LEDC_MODE       LEDC_LOW_SPEED_MODE
#define BUZZER_LEDC_CHANNEL    LEDC_CHANNEL_0
#define BUZZER_LEDC_DUTY_RES   LEDC_TIMER_10_BIT   
#define BUZZER_TONE_FREQ_HZ    2000               
#define BUZZER_DUTY_ON         512                 
#define BUZZER_DUTY_OFF        0 
#endif

// This pure logic remains visible to the native compiler
AlarmState evaluateTemperature(float temp) {
    if (temp < TEMP_THRESHOLD_LOW) {
        return AlarmState::LOW_TEMP;
    } else if (temp > TEMP_THRESHOLD_HIGH) {
        return AlarmState::HIGH_TEMP;
    }
    return AlarmState::NORMAL;
}

// Hide the hardware functions from the native compiler
#ifndef UNIT_TEST
static void init_buzzer_pwm() {
    ledc_timer_config_t timer_conf = {};
    timer_conf.speed_mode = BUZZER_LEDC_MODE;
    timer_conf.duty_resolution = BUZZER_LEDC_DUTY_RES;
    timer_conf.timer_num = BUZZER_LEDC_TIMER;
    timer_conf.freq_hz = BUZZER_TONE_FREQ_HZ;
    timer_conf.clk_cfg = LEDC_AUTO_CLK;
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {};
    channel_conf.gpio_num = BUZZER_PIN;
    channel_conf.speed_mode = BUZZER_LEDC_MODE;
    channel_conf.channel = BUZZER_LEDC_CHANNEL;
    channel_conf.timer_sel = BUZZER_LEDC_TIMER;
    channel_conf.duty = BUZZER_DUTY_OFF;
    channel_conf.hpoint = 0;
    ledc_channel_config(&channel_conf);
}

void vAlarmTask(void *pvParameters) {
    init_buzzer_pwm();

    bool lastAlarmActive = false;

    for (;;) {
        EventBits_t bits = xEventGroupGetBits(g_systemEvents);
        bool alarmActive = (bits & EVENT_ALARM) != 0;

        if (alarmActive != lastAlarmActive) {
            printf("[AlarmTask] Alarm state changed -> %s\n", alarmActive ? "ACTIVE" : "NORMAL");
            lastAlarmActive = alarmActive;
        }

        ledc_set_duty(BUZZER_LEDC_MODE, BUZZER_LEDC_CHANNEL, alarmActive ? BUZZER_DUTY_ON : BUZZER_DUTY_OFF);
        ledc_update_duty(BUZZER_LEDC_MODE, BUZZER_LEDC_CHANNEL);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
#endif