#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <TimeLib.h>
// #include <DS1307RTC.h>
#include <Wire.h>
#include <RtcDS3231.h>

// #include <Aconfig-struct.h>
#include <domopool.pb.h>

#ifndef __ATIME_H_UNDEFINED__
#define __ATIME_H_UNDEFINED__
void initSystemTime(domopool_Config &config, int sda, int scl);
void setSytemTime(bool ethServerStarted, domopool_Config &config);
String printTime(bool seconds);
String printDate();
#endif
