#include "Aconfig.h"

const int ConfigDocSize = 1024;
const char *networkFile = "/network.jsn";
Preferences prefs;
String defaultNtpServer = "fr.pool.ntp.org";
String defaultMQTTServer = "192.168.10.201";

void pref2config(domopool_Config &config)
{
    //default not working
    config.global.ack_tone = prefs.getDouble("ack_tone", 4000);
    strcpy(config.network.ntp.server, prefs.getString("ntp_server", defaultNtpServer).c_str());
    strcpy(config.network.mqtt.server, prefs.getString("mqtt_server", defaultMQTTServer).c_str());
    config.sensors.ph.threshold = prefs.getFloat("ph_threshold", 7.4);

    //no bug
    config.global.lcd_backlight_duration = prefs.getShort("BacklightTime", 30000);
    config.global.ack_duration = prefs.getInt("ackDuration", 100);
    config.global.wdt_duration = prefs.getInt("wdtDuration", 60);
    config.global.serial_out = prefs.getBool("serialOut", true);
    config.global.display_startup = prefs.getBool("displayStartup", false);
    config.global.force_light = prefs.getBool("forceLight", false);

    config.network.ntp.day_light = prefs.getShort("dayLight", 3600);
    config.network.ntp.timezone = prefs.getShort("timeZone", 3600);
    config.network.dhcp = prefs.getBool("dhcp", true);
    config.network.allow_post = prefs.getBool("allowPost", true);
    config.network.mqtt.enabled = prefs.getBool("mqtt_enabled", false);

    config.sensors.ph.enabled = prefs.getBool("ph_enabled", false);
    config.sensors.ph.threshold = prefs.getFloat("ph_threshold", 0);
    config.sensors.ph.threshold_accuracy = prefs.getShort("ph_t_accuracy", 0);
    config.sensors.ph.vmin = prefs.getFloat("ph_vmin", 0);
    config.sensors.ph.vmax = prefs.getFloat("ph_vmax", 0);
    config.sensors.ph.adc_pin = prefs.getShort("ph_adc_pin", 2);
    config.sensors.ph.precision_factor = prefs.getShort("ph_prec_fact", 100);
    config.sensors.ph.auto_cal = prefs.getBool("ph_auto_cal", true);

    config.sensors.ch.enabled = prefs.getBool("ch_enabled", false);
    config.sensors.ch.threshold = prefs.getFloat("ch_threshold", 0);
    config.sensors.ch.threshold_accuracy = prefs.getShort("ch_t_accuracy", 0);
    config.sensors.ch.vmin = prefs.getFloat("ch_vmin", 0);
    config.sensors.ch.vmax = prefs.getFloat("ch_vmax", 0);
    config.sensors.ch.adc_pin = prefs.getShort("ch_adc_pin", 1);
    config.sensors.ch.precision_factor = prefs.getShort("ch_prec_fact", 100);
    config.sensors.ch.auto_cal = prefs.getBool("ch_auto_cal", true);

    config.sensors.wp.enabled = prefs.getBool("wp_enabled", false);
    config.sensors.wp.threshold = prefs.getFloat("wp_threshold", 0.5);
    config.sensors.wp.threshold_accuracy = prefs.getShort("wp_t_accuracy", 8);
    config.sensors.wp.vmin = prefs.getFloat("wp_vmin", 0.5);
    config.sensors.wp.vmax = prefs.getFloat("wp_vmax", 4.5);
    config.sensors.wp.adc_pin = prefs.getShort("wp_adc_pin", 3);
    config.sensors.wp.precision_factor = prefs.getShort("wp_prec_fact", 100);
    config.sensors.wp.auto_cal = prefs.getBool("wp_auto_cal", true);

    config.sensors.wait_for_conversion = prefs.getBool("waitConvertion", true);
    config.sensors.temp_resolution = prefs.getShort("tempResolution", 12);
    config.sensors.precision_factor = prefs.getShort("precisonFact", 10);
    config.sensors.twin.enabled = prefs.getBool("twin_enabled", false);
    config.sensors.twin.init = prefs.getBool("twin_init", false);
    config.sensors.twout.enabled = true;
    config.sensors.twout.init = prefs.getBool("twout_init", false);
    config.sensors.tamb.enabled = true;
    config.sensors.tamb.init = prefs.getBool("tamb_init", false);
    config.sensors.adc_mode = prefs.getShort("adcMode", 1);
    config.sensors.adc_datarate = prefs.getShort("adcDatarate", 1);
    config.sensors.adc_gain = prefs.getShort("adcGain", 1);

    config.pump.force_filter = prefs.getBool("forceFilter", false);
    config.pump.force_ph = prefs.getBool("forcePH", false);
    config.pump.force_ch = prefs.getBool("forceCH", false);
    config.pump.automatic = prefs.getBool("auto", true);
    config.pump.recover = prefs.getBool("recover", false);
    config.pump.force_check = prefs.getBool("forceCheck", false);
    config.pump.force_duration = prefs.getShort("forceDuration", 0);
    config.pump.force_start_time = prefs.getUInt("forceStartTime", 0);

    config.limits.ch_min = prefs.getFloat("ch_min", 0);
    config.limits.ch_max = prefs.getFloat("ch_max", 0);
    config.limits.ph_min = prefs.getFloat("ph_min", 0);
    config.limits.ph_max = prefs.getFloat("ph_max", 0);
    config.limits.wp_min = prefs.getFloat("wp_min", 0.2);
    config.limits.wp_max = prefs.getFloat("wp_max", 2);
    config.limits.ch_temp_threshold_high = prefs.getFloat("ch_t_high", 15);
    config.limits.ch_temp_threshold_low = prefs.getFloat("ch_t_low", 14);
    config.limits.ch_wait_before_allow = prefs.getShort("ch_wait_allow", 24);
    config.limits.ch_wait_before_deny = prefs.getShort("ch_wait_deny", 24);
    config.limits.wp_0_derive = prefs.getFloat("wp_0_derive", 0.01);
    config.limits.tw_min = prefs.getFloat("tw_min", 2);
    config.limits.tw_max = prefs.getFloat("tw_max", 30);
    config.limits.tamb_min = prefs.getFloat("tamb_min", 0);

    config.alarms.reboot = prefs.getBool("reboot", false);
}

bool initConfig()
{
    Serial.println(F("[Conf] Loading configuration..."));
    if (!prefs.begin("domopool"))
    {
        Serial.println(F("[Conf] Unable to start preferences"));
        return false;
    }
    return true;
}

void loadDefaultConfig(domopool_Config &config)
{
    // domopool_Config_init_zero();
    config.has_alarms = true;
    config.alarms.has_ads1115 = true;
    config.has_global = true;
    config.has_metrics = true;
    config.has_network = true;
    config.network.has_mqtt = true;
    config.network.has_ntp = true;
    config.has_pump = true;
    config.has_sensors = true;
    config.sensors.has_ch = true;
    config.sensors.has_ph = true;
    config.sensors.has_tamb = true;
    config.sensors.has_twin = true;
    config.sensors.has_twout = true;
    config.sensors.has_wp = true;
    config.has_states = true;
    config.has_tests = true;
    config.has_limits = true;
    config.alarms.has_mqtt = true;
    boolean init = prefs.getBool("init", false);
    if (!init)
    {
        Serial.println(F("[Conf] Preferences not set; using default."));
        prefs.clear();
        Serial.print("[Conf] free entries: ");
        Serial.println(prefs.freeEntries());
        prefs.putBool("init", true);

        prefs.putDouble("ack_tone", 4000);
        prefs.putString("ntp_server", defaultNtpServer);
        prefs.putString("mqtt_server", defaultMQTTServer);
        prefs.putFloat("ph_threshold", 7.4);
    }
    pref2config(config);
    config.states.startup = true;
    Serial.println(F("[Conf] Done"));
}

void config2pref(domopool_Config &config)
{
    prefs.putBool("dhcp", config.network.dhcp);
    prefs.putBool("allowPost", config.network.allow_post);
    prefs.putBool("twin_enabled", config.sensors.twin.enabled);
    prefs.putBool("waitConvertion", config.sensors.wait_for_conversion);
    prefs.putShort("tempResolution", config.sensors.temp_resolution);
    prefs.putShort("precisonFact", config.sensors.precision_factor);
    prefs.putBool("ph_enabled", config.sensors.ph.enabled);
    prefs.putFloat("ph_threshold", config.sensors.ph.threshold);
    prefs.putShort("ph_t_accuracy", config.sensors.ph.threshold_accuracy);
    prefs.putFloat("ph_vmin", config.sensors.ph.vmin);
    prefs.putFloat("ph_vmax", config.sensors.ph.vmax);
    prefs.putShort("ph_adc_pin", config.sensors.ph.adc_pin);
    prefs.putShort("ph_prec_fact", config.sensors.ph.precision_factor);
    prefs.putBool("ph_auto_cal", config.sensors.ph.auto_cal);
    prefs.putBool("ch_enabled", config.sensors.ch.enabled);
    prefs.putFloat("ch_threshold", config.sensors.ch.threshold);
    prefs.putShort("ch_t_accuracy", config.sensors.ch.threshold_accuracy);
    prefs.putFloat("ch_vmin", config.sensors.ch.vmin);
    prefs.putFloat("ch_vmax", config.sensors.ch.vmax);
    prefs.putShort("ch_adc_pin", config.sensors.ch.adc_pin);
    prefs.putShort("ch_prec_fact", config.sensors.ch.precision_factor);
    prefs.putBool("ch_auto_cal", config.sensors.ch.auto_cal);
    prefs.putBool("wp_enabled", config.sensors.wp.enabled);
    prefs.putFloat("wp_threshold", config.sensors.wp.threshold);
    prefs.putShort("wp_t_accuracy", config.sensors.wp.threshold_accuracy);
    prefs.putFloat("wp_vmin", config.sensors.wp.vmin);
    prefs.putFloat("wp_vmax", config.sensors.wp.vmax);
    prefs.putShort("wp_adc_pin", config.sensors.wp.adc_pin);
    prefs.putShort("wp_prec_fact", config.sensors.wp.precision_factor);
    prefs.putBool("wp_auto_cal", config.sensors.wp.auto_cal);
    prefs.putShort("BacklightTime", config.global.lcd_backlight_duration);
    prefs.putDouble("ack_tone", config.global.ack_tone);
    prefs.putInt("ackDuration", config.global.ack_duration);
    prefs.putInt("wdtDuration", config.global.wdt_duration);
    prefs.putBool("serialOut", config.global.serial_out);
    prefs.putBool("displayStartup", config.global.display_startup);
    prefs.putShort("dayLight", config.network.ntp.day_light);
    prefs.putShort("timeZone", config.network.ntp.timezone);
    prefs.putString("ntp_server", config.network.ntp.server);
    prefs.putBool("forceFilter", config.pump.force_filter);
    prefs.putBool("forcePH", config.pump.force_ph);
    prefs.putBool("forceCH", config.pump.force_ch);
    prefs.putBool("forceLight", config.global.force_light);
    prefs.putBool("forceCheck", config.pump.force_check);
    prefs.putShort("forceDuration", config.pump.force_duration);
    prefs.putUInt("forceStartTime", config.pump.force_start_time);
    prefs.putString("mqtt_server", config.network.mqtt.server);
    prefs.putBool("mqtt_enabled", config.network.mqtt.enabled);
    prefs.putFloat("ch_min", config.limits.ch_min);
    prefs.putFloat("ch_max", config.limits.ch_max);
    prefs.putFloat("ph_min", config.limits.ph_min);
    prefs.putFloat("ph_max", config.limits.ph_max);
    prefs.putFloat("wp_min", config.limits.wp_min);
    prefs.putFloat("wp_max", config.limits.wp_max);
    prefs.putFloat("ch_t_high", config.limits.ch_temp_threshold_high);
    prefs.putFloat("ch_t_low", config.limits.ch_temp_threshold_low);
    prefs.putShort("ch_wait_allow", config.limits.ch_wait_before_allow);
    prefs.putShort("ch_wait_deny", config.limits.ch_wait_before_deny);
    prefs.putFloat("wp_0_derive", config.limits.wp_0_derive);
    prefs.putFloat("tw_min", config.limits.tw_min);
    prefs.putFloat("tw_max", config.limits.tw_max);
    prefs.putFloat("tamb_min", config.limits.tamb_min);
    prefs.putShort("adcMode", config.sensors.adc_mode);
    prefs.putShort("adcDatarate", config.sensors.adc_datarate);
    prefs.putShort("adcGain", config.sensors.adc_gain);
}

void saveConfiguration(domopool_Config &config)
{
    Serial.println(F("[Conf] Saving config to preferences"));
    config2pref(config);
    Serial.println(F("[Conf] Done"));
}

void initConfigData(domopool_Config &config)
{
    config.states.startup = true;
    config.states.filter_on = false;
    config.states.ph_on = false;
    prefs.putBool("reboot", false);
    config.alarms.reboot = false;
}

bool stopRelay(const int8_t p)
{
    switch (p)
    {
    case domopool_Relay_names_filter:
        unsetRelayAuto();
        prefs.putBool("forceFilter", false);
        prefs.putBool("forceCH", false);
        prefs.putBool("forcePH", false);
        break;
    case domopool_Relay_names_ch:
        unsetRelayAuto();
        prefs.putBool("forceCH", false);
        break;
    case domopool_Relay_names_ph:
        unsetRelayAuto();
        prefs.putBool("forcePH", false);
        break;
        // stop light
        // case domopool_Relay_names_light:
        //     prefs.putBool("forceLight", false);
        //     break;

    default:
        return false;
        break;
    }
    prefs.putShort("forceDuration", 0);
    return true;
}

bool startRelay(const int8_t p, uint32_t duration)
{
    switch (p)
    {
    // start filter
    case domopool_Relay_names_filter:
        unsetRelayAuto();
        prefs.putBool("forceFilter", true);
        prefs.putBool("forceCH", false);
        prefs.putBool("forcePH", false);
        break;
    // start ch
    case domopool_Relay_names_ch:
        unsetRelayAuto();
        prefs.putBool("forceFilter", true);
        prefs.putBool("forceCH", true);
        break;
    // start ph
    case domopool_Relay_names_ph:
        unsetRelayAuto();
        prefs.putBool("forceFilter", true);
        prefs.putBool("forcePH", true);
        break;
    // start light
    // case domopool_Relay_names_light:
    //     prefs.putBool("forceLight", true);
    //     break;
    // all relay
    // case 4:
    //     prefs.putBool("auto", false);
    //     prefs.putBool("forceFilter", true);
    //     prefs.putBool("forceCH", true);
    //     prefs.putBool("forcePH", true);
    //     break;
    default:
        return false;
        break;
    }
    prefs.putShort("forceDuration", duration);
    prefs.putUInt("forceStartTime", now());
    return true;
}

void unsetRelayAuto()
{
    prefs.putBool("auto", false);
    prefs.putBool("recover", false);
    prefs.putShort("forceDuration", 0);
}

void setRelayAuto()
{
    prefs.putBool("auto", true);
    prefs.putBool("recover", false);
    prefs.putBool("forceFilter", false);
    prefs.putBool("forceCH", false);
    prefs.putBool("forcePH", false);
    prefs.putShort("forceDuration", 0);
}

void unsetRelayAutoRecover()
{
    prefs.putBool("recover", false);
}

void setRelayAutoRecover()
{
    setRelayAuto();
    prefs.putBool("recover", true);
}

void unsetForceCheck()
{
    prefs.putBool("forceCheck", false);
}
void startMqtt()
{
    prefs.putBool("mqtt_enabled", true);
}
void stopMqtt()
{
    prefs.putBool("mqtt_enabled", false);
}
void setMqtt(String server)
{
    prefs.putString("mqtt_server", server);
}

void resetConfig()
{
    prefs.putBool("init", false);
}

void reboot()
{
    Serial.println(F("[WiFi] System asked to reboot"));
    prefs.putBool("reboot", true);
}

void setADC(domopool_Sensors &sens)
{
    prefs.putShort("adcMode", sens.adc_mode);
    prefs.putShort("adcGain", sens.adc_gain);
    prefs.putShort("adcDatarate", sens.adc_datarate);
}

void setWP(domopool_AnalogSensor &analog)
{
    prefs.putFloat("wp_threshold", analog.threshold);
    prefs.putInt("wp_t_accuracy", analog.threshold_accuracy);
    prefs.putInt("wp_adc_pin", analog.adc_pin);
    prefs.putFloat("wp_vmin", analog.vmin);
    prefs.putFloat("wp_vmax", analog.vmax);
    prefs.putBool("wp_auto_cal", analog.auto_cal);
}

void enableWP()
{
    prefs.putBool("wp_enabled", true);
}

void disableWP()
{
    prefs.putBool("wp_enabled", false);
}

void setPH(domopool_AnalogSensor &analog)
{
    prefs.putFloat("ph_threshold", analog.threshold);
    prefs.putInt("ph_t_accuracy", analog.threshold_accuracy);
    prefs.putInt("ph_adc_pin", analog.adc_pin);
    prefs.putFloat("ph_vmin", analog.vmin);
    prefs.putFloat("ph_vmax", analog.vmax);
    prefs.putBool("ph_auto_cal", analog.auto_cal);
}

void enablePH()
{
    prefs.putBool("ph_enabled", true);
}

void disablePH()
{
    prefs.putBool("ph_enabled", false);
}

void setCH(domopool_AnalogSensor &analog)
{
    prefs.putFloat("ch_threshold", analog.threshold);
    prefs.putInt("ch_t_accuracy", analog.threshold_accuracy);
    prefs.putInt("ch_adc_pin", analog.adc_pin);
    prefs.putFloat("ch_vmin", analog.vmin);
    prefs.putFloat("ch_vmax", analog.vmax);
    prefs.putBool("ch_auto_cal", analog.auto_cal);
}

void enableCH()
{
    prefs.putBool("ch_enabled", true);
}

void disableCH()
{
    prefs.putBool("ch_enabled", false);
}

void setLimits(domopool_Limits &limits)
{
    prefs.putFloat("ch_min", limits.ch_min);
    prefs.putFloat("ch_max", limits.ch_max);
    prefs.putFloat("ph_min", limits.ph_min);
    prefs.putFloat("ph_max", limits.ph_max);
    prefs.putFloat("wp_min", limits.wp_min);
    prefs.putFloat("wp_max", limits.wp_max);
    prefs.putFloat("ch_t_high", limits.ch_temp_threshold_high);
    prefs.putFloat("ch_t_low", limits.ch_temp_threshold_low);
    prefs.putShort("ch_wait_allow", limits.ch_wait_before_allow);
    prefs.putShort("ch_wait_deny", limits.ch_wait_before_deny);
    prefs.putFloat("wp_0_derive", limits.wp_0_derive);
    prefs.putFloat("tw_min", limits.tw_min);
    prefs.putFloat("tw_max", limits.tw_max);
    prefs.putFloat("tamb_min", limits.tamb_min);
}

void alarms2doc(domopool_Config &config, JsonDocument &doc)
{
    // doc["alarms"]["adsNotConnect"] = config.alarms.ads1115.not_connected;
    // doc["alarms"]["adsNotReady"] = config.alarms.ads1115.not_ready;
    // doc["alarms"]["adsNotStarted"] = config.alarms.ads1115.not_started;
    doc["alarms"]["ch"] = config.alarms.ch;
    doc["alarms"]["filter"] = config.alarms.filter;
    // doc["alarms"]["mqttMetrics"] = config.alarms.mqtt.metrics;
    // doc["alarms"]["mqttStates"] = config.alarms.mqtt.states;
    // doc["alarms"]["mqttAlarms"] = config.alarms.mqtt.alarms;
    doc["alarms"]["ph"] = config.alarms.ph;
    doc["alarms"]["rtc"] = config.alarms.rtc;
    doc["alarms"]["tambFrost"] = config.alarms.tamb_frost;
    doc["alarms"]["twFrost"] = config.alarms.tw_frost;
    // doc["alarms"]["twHigh"] = config.alarms.tw_high;
    doc["alarms"]["wpBroken"] = config.alarms.wp_broken;
    doc["alarms"]["wpHigh"] = config.alarms.wp_high;
    doc["alarms"]["wpLow"] = config.alarms.wp_low;
    doc["alarms"]["reboot"] = config.alarms.reboot;
}

void metrics2doc(domopool_Config &config, JsonDocument &doc)
{
    doc["metrics"]["overChTempDuration"] = config.metrics.over_ch_t_high_duration;
    doc["metrics"]["underChTempDuration"] = config.metrics.under_ch_t_low_duration;
    doc["metrics"]["ch"] = config.metrics.ch;
    doc["metrics"]["ph"] = config.metrics.ph;
    doc["metrics"]["wp"] = config.metrics.wp;
    doc["metrics"]["wpVolt"] = config.metrics.wp_volt;
    doc["metrics"]["time"] = config.metrics.time;
}

void temps2doc(domopool_Config &config, JsonDocument &doc)
{
    doc["metrics"]["tamb"] = config.metrics.tamb;
    doc["metrics"]["twater"] = config.metrics.twater;
    doc["metrics"]["hour"] = config.metrics.hour;
    doc["metrics"]["savedTwater"] = config.metrics.saved_twater;
}

void states2doc(domopool_Config &config, JsonDocument &doc)
{
    doc["states"]["filterOn"] = config.states.filter_on;
    doc["states"]["phOn"] = config.states.ph_on;
    doc["states"]["chOn"] = config.states.ch_on;
    doc["states"]["automatic"] = config.states.automatic;
    doc["states"]["startup"] = config.states.startup;
    doc["states"]["ntp"] = config.states.ntp;
    doc["states"]["rtc"] = config.states.rtc;
    doc["states"]["netActive"] = config.states.net_active;
    doc["states"]["lightOn"] = config.states.light_on;
    doc["states"]["recover"] = config.states.recover;
}
