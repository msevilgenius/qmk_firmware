#include "solenoid.h"

#include <avr/io.h>
#include <timer.h>
#include "pincontrol.h"

int  solenoid_timer  = 0;
bool solenoid_enabled = false;
bool solenoid_on     = false;
volatile uint32_t solenoid_start = 0;
uint8_t solenoid_dwell = SOLENOID_DEFAULT_DWELL;

void solenoid_setup(void) {
    pinMode(SOLENOID_PIN, PinDirectionOutput);
    timer_init();
}

void solenoid_update(void) {
    uint16_t elapsed = 0;

    if (!solenoid_on) return;

    elapsed = timer_elapsed32(solenoid_start);

    // Check if it's time to finish this solenoid click cycle
    if (elapsed > solenoid_dwell) {
        digitalWrite(SOLENOID_PIN, PinLevelLow);
        return;
    }
}

void solenoid_trigger(void) {
    if (!solenoid_enabled) {
        return;
    }
    solenoid_on    = true;
    solenoid_start = timer_read32();
    digitalWrite(SOLENOID_PIN, PinLevelHigh);
}

void solenoid_enable(void) { solenoid_enabled = true; }

void solenoid_disable(void) { solenoid_enabled = false; }

void solenoid_enabled_toggle(void) { solenoid_enabled = !solenoid_enabled; }

bool is_solenoid_enabled(void) { return solenoid_enabled; }
