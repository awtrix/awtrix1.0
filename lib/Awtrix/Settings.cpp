#include <Settings.h>
#include "FS.h"

void AwtrixSettings::initialise() {
    if (!SPIFFS.begin()) {
        Serial.println(F("Failed to mount file system"));
        // TODO: Add exception
    }

    File configFile = SPIFFS.open(filename, "r");
    if (!configFile) {
        Serial.println(F("Creating default settings"));
        loadDefaultSettings();
        saveSettings();

        return;
    }

    size_t size = configFile.size();
    if (size > 2048) { // 2 KiB
        Serial.println(F("Config file size is too large"));
    }

    Serial.println(F("Config file loaded"));
    std::unique_ptr<char[]> buf(new char[size]);

    configFile.readBytes(buf.get(), size);
    configFile.close();

    StaticJsonBuffer<200> jsonBuffer;
    dataObject = &jsonBuffer.parseObject(buf.get());

    if (!dataObject->success()) {
        Serial.println(F("Failed to parse config file"));
    }
    dataObject->printTo(Serial);
}

void AwtrixSettings::parseSettings(char json[]) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
        Serial.println(F("parseObject() failed"));
        return;
    }

    if (root.containsKey("brightness")) (*dataObject)["brightness"] = root["brightness"];
    if (root.containsKey("showIpOnBoot")) (*dataObject)["showIpOnBoot"] = root["showIpOnBoot"];
    if (root.containsKey("enableHeartbeat")) (*dataObject)["enableHeartbeat"] = root["enableHeartbeat"];
    if (root.containsKey("enableAutoBrightness")) (*dataObject)["enableAutoBrightness"] = root["enableAutoBrightness"];
    if (root.containsKey("scrollInterval")) (*dataObject)["scrollInterval"] = root["scrollInterval"];
    if (root.containsKey("utcOffset")) (*dataObject)["utcOffset"] = root["utcOffset"];
    if (root.containsKey("isMetric")) (*dataObject)["isMetric"] = root["isMetric"];
    if (root.containsKey("wundergroundApiKey")) (*dataObject)["wundergroundApiKey"] = root["wundergroundApiKey"];
    if (root.containsKey("wundergroundLanguage")) (*dataObject)["wundergroundLanguage"] = root["wundergroundLanguage"];
    if (root.containsKey("wundergroundZmwCode")) (*dataObject)["wundergroundZmwCode"] = root["wundergroundZmwCode"];
    saveSettings();
}

void AwtrixSettings::loadDefaultSettings() {
    DynamicJsonBuffer jsonBuffer(bufferSize);
    dataObject = &jsonBuffer.createObject();

    (*dataObject)["brightness"] = 100;
    (*dataObject)["showIpOnBoot"] = false;
    (*dataObject)["enableHeartbeat"] = false;
    (*dataObject)["enableAutoBrightness"] = false;
    (*dataObject)["scrollInterval"] = 75;
    (*dataObject)["utcOffset"] = 1;
    (*dataObject)["isMetric"] = false;
    (*dataObject)["wundergroundApiKey"] = "b9cd2ae34c2974b6";
    (*dataObject)["wundergroundLanguage"] = "DE";
    (*dataObject)["wundergroundZmwCode"] = "0000.2150.10348";
}

bool AwtrixSettings::saveSettings() {
    File configFile = SPIFFS.open(filename, "w");
    if (!configFile) {
        Serial.println(F("Failed to open config file for writing"));
        return false;
    }

    dataObject->printTo(configFile);
    configFile.close();

    Serial.println(F("Config file saved"));
    return true;
}
