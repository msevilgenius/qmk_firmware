#ifndef SOLENOID_H
#define SOLENOID_H

#include "quantum.h"

#ifndef SOLENOID_PIN
#define SOLENOID_PIN B7
#endif // SOLENOID_PIN

#ifndef SOLENOID_DEFAULT_DWELL
#define SOLENOID_DEFAULT_DWELL 30
#endif // SOLENOID_DEFAULT_DWELL


/* Add to matrix_init_user */
void solenoid_setup(void);

/* Add to matrix_scan_user */
void solenoid_update(void);

/*

Add wherever you want to trigger the solenoid,
I suggest adding the following to process_record_user:

if (record->event.pressed) {
    solenoid_trigger();
}

*/
void solenoid_trigger(void);

/* Use these functions in your keymap as you see fit */
void solenoid_enable(void);
void solenoid_disable(void);
void solenoid_enabled_toggle(void);
bool is_solenoid_enabled(void);


#endif // SOLENOID_H
