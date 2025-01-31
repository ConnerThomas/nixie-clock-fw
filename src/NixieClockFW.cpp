#include <Arduino.h>
#include "NixieClockFW.h"

#include <TimeLib.h>
#include <Tone.h>

#include "Menu.h"
#include "Display.h"
#include "TimeKeeper.h"
//#include "RTTTL.h"

#if _CONFIG_GPS_ENABLED
#include "GPSTime.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////

using NixieClock::Display;
using NixieClock::DisplayACP;
using NixieClock::Menu;

// RTTTL alarmMusic;

void display_update();

#if _CONFIG_GPS_ENABLED
void gps_sync();
#endif

bool SLEEP;

//// SETUP ///////////////////////////////////////////////////////////////////////////
void setup()
{

  Serial.begin(230400); // lowered this from 230400, probably doesn't need to be that high

  Serial.write("Conner's Fork of H3xCat's NixieClock Firmware (" NCS_STR ")\r\n");

  SLEEP = false;

  Display.begin();
  TimeKeeper.begin();


#if _CONFIG_GPS_ENABLED
  GPSTime.begin(false, &Serial1);
#endif

  Menu.begin();

  // // Enable anti-cathode-poisoning
  Display.setACP(DisplayACP::ALL, 60000, 500);

  TimeKeeper.setDst(DST::USA);
  TimeKeeper.setOffset(0);

  //alarmMusic.begin(PIN_BUZZER);
  //alarmMusic.load((char *)"Auld L S:d=4,o=6,b=101:g5,c,8c,c,e,d,8c,d,8e,8d,c,8c,e,g,2a,a,g,8e,e,c,d,8c,d,8e,8d,c,8a5,a5,g5,2c");
  //  alarmMusic.play();

  Display.wipeAnimate();

}

//// LOOP ////////////////////////////////////////////////////////////////////////////
void loop()
{
  Display.update();
  Menu.update();
  //alarmMusic.update();

  if (Menu.buttonState(BUTTON_UP))
  {
  }

#if _CONFIG_GPS_ENABLED
  GPSTime.update();
  gps_sync();
#endif

  display_update();
}

//////////////////////////////////////////////////////////////////////////////////////

#if _CONFIG_GPS_ENABLED
void gps_sync()
{
  static uint32_t last_updated = _CONFIG_GPS_SYNC_INTERVAL;

  if (millis() - last_updated <= _CONFIG_GPS_SYNC_INTERVAL)
    return;

  switch (GPSTime.getStatus())
  {
  case IDLE:
    GPSTime.request();
    Serial.println("Initiating GPS sync.");
    break;
  case WAITING:
    break;
  case FINISHED:
    last_updated = millis();

    GPSTime.reset();

    TimeElements timeinfo_utc = {};

    GPSTime.getUtcTime(&timeinfo_utc);

    time_t time_utc = makeTime(timeinfo_utc);
    time_t latency = GPSTime.millisSinceUpdate();

    delay(1000 - (latency % 1000));
    time_utc += (latency / 1000) + 1;

    TimeKeeper.setEpoch(time_utc);

    Serial.print("GPS Sync ");
    Serial.println(time_utc, DEC);
    Serial.write("\r\n");
    break;
  }
}
#endif

void display_update()
{
  static uint32_t last_updated = _CONFIG_NIXIE_UPDATE_INTERVAL;
  if (millis() - last_updated <= _CONFIG_NIXIE_UPDATE_INTERVAL)
    return;
  last_updated = millis();

  TimeElements timeinfo_local = {};
  TimeKeeper.getLocalTime(timeinfo_local);

  SLEEP = (timeinfo_local.Hour >= SLEEP_START) | (timeinfo_local.Hour < SLEEP_END);

  /** TODO:
   * if we're not in sleep, display time
   * if we are in sleep, only blink colons and turn off ACP
   * 
  */

  if (Menu.buttonState(BUTTON_UP) || Menu.buttonState(BUTTON_DOWN) || Menu.buttonState(BUTTON_MODE))
  {
    // Display date when any of the buttons are pressed down
    Display.setNumber(((unsigned long)timeinfo_local.Month) * 10000 + timeinfo_local.Day * 100 + (((unsigned long)timeinfo_local.Year) % 100));
    Display.setDots(true, false, true, false);

    Display.setLed(100, 100, 0);
  }
  
  if(!SLEEP)
  {
    // Not sure what the 1970 thing was doing, removed since the date cannot be set from the clock
    // Added % 12 to hours to display in 12 hours format, but now 12AM = 00 on the clock
    Display.setNumber(((unsigned long)timeinfo_local.Hour) * 10000 + timeinfo_local.Minute * 100 + timeinfo_local.Second);
    Display.setLed(0, 0, 0);
  }
  else
  {
    digitalWrite(PIN_HV5122_OE, LOW);
  }

  if (timeinfo_local.Second & 0x01)
  {
    Display.setDots(true);
    // Display.setLed(255,0,0);
  }
  else
  {
    Display.setDots(false);
    // Display.setLed(0,0,0);
  }

}
