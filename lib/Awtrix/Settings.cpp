#include <Settings.h>
#include "FS.h"

Settings::Settings() {
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        // TODO: Add exception
    }

    File configFile = SPIFFS.open(filename, "r");
    if (!configFile) {
        Serial.println("Creating default settings");
        loadDefaultSettings();
        saveSettings();

        return;
    }

    size_t size = configFile.size();
    if (size > 2048) { // 2 KiB
        Serial.println("Config file size is too large");
    }

    Serial.println("Config file loaded");
    std::unique_ptr<char[]> buf(new char[size]);

    configFile.readBytes(buf.get(), size);
    configFile.close();

    StaticJsonBuffer<200> jsonBuffer;
    dataObject = &jsonBuffer.parseObject(buf.get());

    if (!dataObject->success()) {
        Serial.println("Failed to parse config file");
    }
}

void Settings::loadDefaultSettings() {
    DynamicJsonBuffer jsonBuffer(bufferSize);
    dataObject = &jsonBuffer.createObject();

    (*dataObject)["brightness"] = 0;
    (*dataObject)["showIpOnBoot"] = false;
    (*dataObject)["enableHeartbeat"] = false;
    (*dataObject)["enableAutoBrightness"] = false;
    (*dataObject)["scrollInterval"] = 75;
    (*dataObject)["utcOffset"] = 1;
    (*dataObject)["isMetric"] = false;
    (*dataObject)["wundergroundApiKey"] = "123";
    (*dataObject)["wundergroundLanguage"] = "de";
    (*dataObject)["wundergroundCity"] = "de";
    (*dataObject)["wundergroundCountry"] = "de";
    (*dataObject)["wundergroundZmwCode"] = "de";
}

bool Settings::saveSettings() {
    File configFile = SPIFFS.open(filename, "w");
    if (!configFile) {
        Serial.println("Failed to open config file for writing");
        return false;
    }

    dataObject->printTo(configFile);
    configFile.close();

    Serial.println("Config file saved");
    return true;
}
