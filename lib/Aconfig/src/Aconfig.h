#include <Arduino.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <TimeLib.h>
#include <domopool.pb.h>

#ifndef __ACONFIG_H__
#define __ACONFIG_H__
bool initConfig();
void loadDefaultConfig(domopool_Config &config);
void saveConfiguration(domopool_Config &config);
void initConfigData(domopool_Config &config);
bool stopRelay(const int8_t p);
bool startRelay(const int8_t p, uint32_t duration);
bool setRelayAuto();
bool unsetRelayAuto();
void pref2config(domopool_Config &config);
void config2pref(domopool_Config &config);
void unsetForceCheck();
void startMqtt();
void stopMqtt();
void setMqtt(String server);
void resetConfig();
void reboot();
void setWP(int adc_pin, float threshold, int taccuracy, float vmin, float vmax);
void enableWP();
void disableWP();
void setPH(int adc_pin, float threshold, int taccuracy, float vmin, float vmax);
void disablePH();
void setCH(int adc_pin, float threshold, int taccuracy, float vmin, float vmax);
void disableCH();
void metrics2doc(domopool_Config &config, JsonDocument &doc);
void states2doc(domopool_Config &config, JsonDocument &doc);
#endif
