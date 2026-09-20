#include <unity.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "alarm.h"
#include "system_state.h"

void setUp(void) {}
void tearDown(void) {}

// --- Category: Temperature alarm logic[cite: 2] ---
void test_temp_below_lower_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::LOW_TEMP, evaluateTemperature(15.0f)); // Below lower threshold[cite: 2]
}
void test_temp_exactly_lower_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::NORMAL, evaluateTemperature(18.0f));   // Exactly lower threshold[cite: 2]
}
void test_temp_normal_value(void) {
    TEST_ASSERT_EQUAL(AlarmState::NORMAL, evaluateTemperature(24.0f));   // Normal value[cite: 2]
}
void test_temp_exactly_upper_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::NORMAL, evaluateTemperature(30.0f));   // Exactly upper threshold[cite: 2]
}
void test_temp_above_upper_threshold(void) {
    TEST_ASSERT_EQUAL(AlarmState::HIGH_TEMP, evaluateTemperature(35.0f)); // Above upper threshold[cite: 2]
}

// --- Category: Display navigation[cite: 2] ---
void test_display_forward_transition(void) {
    TEST_ASSERT_EQUAL(DisplayMode::HUMIDITY, getNextDisplayMode(DisplayMode::TEMPERATURE)); // Forward transition[cite: 2]
}
void test_display_reverse_transition(void) {
    TEST_ASSERT_EQUAL(DisplayMode::TEMPERATURE, getPreviousDisplayMode(DisplayMode::HUMIDITY)); // Reverse transition[cite: 2]
}
void test_display_forward_wraparound(void) {
    TEST_ASSERT_EQUAL(DisplayMode::TEMPERATURE, getNextDisplayMode(DisplayMode::MOTION)); // Forward wraparound[cite: 2]
}
void test_display_reverse_wraparound(void) {
    TEST_ASSERT_EQUAL(DisplayMode::MOTION, getPreviousDisplayMode(DisplayMode::TEMPERATURE)); // Reverse wraparound[cite: 2]
}

// --- Category: System state[cite: 2] ---
void test_state_active_no_timeout(void) {
    TEST_ASSERT_EQUAL(SystemState::ACTIVE, evaluateSystemState(SystemState::ACTIVE, false, 5000, 15000)); // ACTIVE/no timeout[cite: 2]
}
void test_state_active_with_timeout(void) {
    TEST_ASSERT_EQUAL(SystemState::INACTIVE, evaluateSystemState(SystemState::ACTIVE, false, 15000, 15000)); // ACTIVE/timeout[cite: 2]
}
void test_state_inactive_no_motion(void) {
    TEST_ASSERT_EQUAL(SystemState::INACTIVE, evaluateSystemState(SystemState::INACTIVE, false, 0, 15000)); // INACTIVE/no motion[cite: 2]
}
void test_state_inactive_with_motion(void) {
    TEST_ASSERT_EQUAL(SystemState::ACTIVE, evaluateSystemState(SystemState::INACTIVE, true, 0, 15000)); // INACTIVE/motion[cite: 2]
}

extern "C" void app_main(void) {
    // Brief delay to allow Wokwi's Serial Monitor to connect before Unity prints results
    vTaskDelay(pdMS_TO_TICKS(2000)); 

    UNITY_BEGIN();
    
    RUN_TEST(test_temp_below_lower_threshold);
    RUN_TEST(test_temp_exactly_lower_threshold);
    RUN_TEST(test_temp_normal_value);
    RUN_TEST(test_temp_exactly_upper_threshold);
    RUN_TEST(test_temp_above_upper_threshold);

    RUN_TEST(test_display_forward_transition);
    RUN_TEST(test_display_reverse_transition);
    RUN_TEST(test_display_forward_wraparound);
    RUN_TEST(test_display_reverse_wraparound);

    RUN_TEST(test_state_active_no_timeout);
    RUN_TEST(test_state_active_with_timeout);
    RUN_TEST(test_state_inactive_no_motion);
    RUN_TEST(test_state_inactive_with_motion);

    UNITY_END();

    fflush(stdout);
}