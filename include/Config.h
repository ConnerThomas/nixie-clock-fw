//////////////////////////////////////////////////////////////////////////////////////
// START OF CONFIG ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _CONFIG_H
#define _CONFIG_H

#define _CONFIG_NIXIE_UPDATE_INTERVAL 200 * ONE_MILLISECOND

#define _CONFIG_GPS_ENABLED 0 // Enables GPS synchronization on Mega boards
#define _CONFIG_GPS_SYNC_INTERVAL 30 * ONE_MINUTE

#define _CONFIG_IR_ENABLED 0 // Enables IR remote functionality

// Define the sleep period where the tubes are powered off
#define SLEEP_START 22 // 10PM
#define SLEEP_END 8 // 8AM
#define COLONS_WHILE_SLEEPING true; // Continue to blink the colons in sleep mode

#define NCS314
// #define NCS318

//////////////////////////////////////////////////////////////////////////////////////
// END OF CONFIG /////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Pin Configurations ////////////////////////////////////////////////////////////////
#if defined(NCS314)
#define PIN_HV5122_OE 10
#define PIN_LED_RED 9
#define PIN_LED_GREEN 6
#define PIN_LED_BLUE 3
#define PIN_BUZZER 2
#define PIN_BTN_UP A2
#define PIN_BTN_DOWN A1
#define PIN_BTN_MODE A0
#elif defined(NCS318)
#define PIN_HV5122_OE 10
// #define PIN_LED_RED 9
// #define PIN_LED_GREEN 6
// #define PIN_LED_BLUE 3
#define PIN_LED 6
#define NUMLED 8
#define PIN_BUZZER 2
#define PIN_BTN_UP A2
#define PIN_BTN_DOWN A1
#define PIN_BTN_MODE A0
#endif

#endif
//////////////////////////////////////////////////////////////////////////////////////
