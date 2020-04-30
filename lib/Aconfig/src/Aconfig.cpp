#include "Aconfig.h"

// Loads the configuration from a file
void loadConfiguration(const char *filename, Config &config)
{
    // Open file for reading
    File file = SD.open(filename);

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<AconfigDocSize> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.println(F("[Conf] Failed to read file, using default configuration"));
        doc["network"]["dhcp"] = true;
        for (int i = 0; i < 8; i++)
        {
            doc["sensors"]["tin"]["addr"][i] = 0;
            doc["sensors"]["tout"]["addr"][i] = 0;
        }
        doc["sensors"]["tin"]["enabled"] = false;
        doc["sensors"]["tdht"]["enabled"] = true;
        doc["sensors"]["waitForConvertion"] = false;
        doc["sensors"]["tempResolution"] = 12;
        doc["sensors"]["ph"]["enabled"] = false;
        doc["sensors"]["ph"]["threshold"] = 7.4;
        doc["global"]["lcdBacklightDuration"] = 30000; // 30s
        doc["time"]["initialized"] = false;
        doc["time"]["dayLight"] = true;
        doc["time"]["ntpServer"] = "europe.pool.ntp.org";
        doc["time"]["timeZone"] = 2;
    }

    // Copy values from the JsonDocument to the Config
    config.global.lcdBacklightDuration = doc["global"]["lcdBacklightDuration"];
    config.time.initialized = doc["time"]["initialized"];
    config.time.dayLight = doc["time"]["dayLight"];
    config.time.ntpServer = doc["time"]["ntpServer"];
    config.time.timeZone = doc["time"]["timeZone"];
    config.netConfig.dhcp = doc["network"]["dhcp"];
    config.netConfig.ip = doc["network"]["ip"];
    config.netConfig.gateway = doc["network"]["gateway"];
    config.netConfig.netmask = doc["network"]["netmask"];
    config.netConfig.dns = doc["network"]["dns"];
    config.sensConfig.ph.enabled = doc["sensors"]["ph"]["enabled"];
    config.sensConfig.ph.threshold = doc["sensors"]["ph"]["threshold"];
    config.sensConfig.waitForConversion = doc["sensors"]["waitForConvertion"];
    config.sensConfig.tempResolution = doc["sensors"]["tempResolution"];
    config.sensConfig.tin.enabled = doc["sensors"]["tin"]["enabled"];
    for (int i = 0; i < 8; i++)
    {
        config.sensConfig.tin.addr[i] = doc["sensors"]["tin"]["addr"][i];
    }
    config.sensConfig.tout.enabled = true;
    for (int i = 0; i < 8; i++)
    {
        config.sensConfig.tout.addr[i] = doc["sensors"]["tout"]["addr"][i];
    }
    config.sensConfig.tdht.enabled = doc["sensors"]["tdht"]["enabled"];

    // Close the file (Curiously, File's destructor doesn't close the file)
    file.close();
}

// Saves the configuration to a file
bool saveConfiguration(const char *filename, Config &config)
{
    // Delete existing file, otherwise the configuration is appended to the file
    char *file2remove;
    file2remove = const_cast<char *>(filename);
    SD.remove(file2remove);

    Serial.print("[Conf] Opening ");
    Serial.print(filename);
    Serial.println(F("..."));
    // Open file for writing
    File file = SD.open(filename, FILE_WRITE);
    if (!file)
    {
        Serial.println(F("Failed to create file"));
        return false;
    }

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<AconfigDocSize> doc = convert2doc(config);

    // Serialize JSON to file
    if (serializeJson(doc, file) == 0)
    {
        Serial.println(F("Failed to write to file"));
        return false;
    }

    // Close the file
    file.close();
    return true;
}

// Saves the configuration to a file
StaticJsonDocument<AconfigDocSize> convert2doc(Config &config)
{
    StaticJsonDocument<AconfigDocSize> doc;

    // Set the values in the document
    doc["global"]["lcdBacklightDuration"] = config.global.lcdBacklightDuration;
    doc["time"]["initialized"] = config.time.initialized;
    doc["time"]["dayLight"] = config.time.dayLight;
    doc["time"]["ntpServer"] = config.time.ntpServer;
    doc["time"]["timeZone"] = config.time.timeZone;
    doc["network"]["dhcp"] = config.netConfig.dhcp;
    doc["network"]["ip"] = config.netConfig.ip;
    doc["network"]["gateway"] = config.netConfig.gateway;
    doc["network"]["netmask"] = config.netConfig.netmask;
    doc["network"]["dns"] = config.netConfig.dns;
    doc["sensors"]["waitForConvertion"] = config.sensConfig.waitForConversion;
    doc["sensors"]["tempResolution"] = config.sensConfig.tempResolution;
    doc["sensors"]["tin"]["enabled"] = config.sensConfig.tin.enabled;
    doc["sensors"]["tin"]["val"] = config.sensConfig.tin.val;
    for (int i = 0; i < 8; i++)
    {
        doc["sensors"]["tin"]["addr"][i] = config.sensConfig.tin.addr[i];
    }

    doc["sensors"]["tout"]["enabled"] = true;
    doc["sensors"]["tout"]["val"] = config.sensConfig.tout.val;
    for (int i = 0; i < 8; i++)
    {
        doc["sensors"]["tout"]["addr"][i] = config.sensConfig.tout.addr[i];
    }
    doc["sensors"]["tdht"]["enabled"] = config.sensConfig.tdht.enabled;
    doc["sensors"]["tdht"]["val"] = config.sensConfig.tdht.val;
    doc["sensors"]["ph"]["enabled"] = config.sensConfig.ph.enabled;
    doc["sensors"]["ph"]["threshold"] = config.sensConfig.ph.threshold;
    doc["sensors"]["ph"]["val"] = config.sensConfig.ph.val;

    return doc;
}

Config convert2config(String data)
{
    StaticJsonDocument<AconfigDocSize> doc;
    deserializeJson(doc, data);
    // DeserializationError error = deserializeJson(doc, data);

    Config config;
    config.global.lcdBacklightDuration = doc["global"]["lcdBacklightDuration"];
    config.time.initialized = doc["time"]["initialized"];
    config.time.dayLight = doc["time"]["dayLight"];
    config.time.ntpServer = doc["time"]["ntpServer"];
    config.time.timeZone = doc["time"]["timeZone"];
    config.netConfig.dhcp = doc["network"]["dhcp"];
    config.netConfig.ip = doc["network"]["ip"];
    config.netConfig.gateway = doc["network"]["gateway"];
    config.netConfig.netmask = doc["network"]["netmask"];
    config.netConfig.dns = doc["network"]["dns"];
    config.sensConfig.ph.enabled = doc["sensors"]["ph"]["enabled"];
    config.sensConfig.ph.threshold = doc["sensors"]["ph"]["threshold"];
    config.sensConfig.waitForConversion = doc["sensors"]["waitForConvertion"];
    config.sensConfig.tempResolution = doc["sensors"]["tempResolution"];
    config.sensConfig.tin.enabled = doc["sensors"]["tin"]["enabled"];
    for (int i = 0; i < 8; i++)
    {
        config.sensConfig.tin.addr[i] = doc["sensors"]["tin"]["addr"][i];
    }
    config.sensConfig.tout.enabled = true;
    for (int i = 0; i < 8; i++)
    {
        config.sensConfig.tout.addr[i] = doc["sensors"]["tout"]["addr"][i];
    }
    config.sensConfig.tdht.enabled = doc["sensors"]["tdht"]["enabled"];
    return config;
}

// Prints the content of a file to the Serial
void printFile(const char *filename)
{
    // Open file for reading
    File file = SD.open(filename);
    if (!file)
    {
        Serial.println(F("Failed to read file"));
        return;
    }

    // Extract each characters by one by one
    while (file.available())
    {
        Serial.print((char)file.read());
    }
    Serial.println();

    // Close the file
    file.close();
}
