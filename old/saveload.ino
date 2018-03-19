#include <ArduinoJson.h>
#include "FS.h"

String loadConfig() {
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return "ERROR";
    }

    File configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
        Serial.println("Writing default Settings");
        saveConfig();
        return "ERROR";
    }

    size_t size = configFile.size();
    Serial.println(size);
    if (size > 2048) {
        Serial.println("Config file size is too large");
        return "ERROR";
    }
    Serial.println("Config file loaded");
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);

    configFile.readBytes(buf.get(), size);
    configFile.close();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf.get());

    if (!json.success()) {
        Serial.println("Failed to parse config file");
        return "ERROR";
    }

    SHOW_IP_ON_BOOT= json["SHOW_IP_ON_BOOT"];
    AUTO_BRIGHTNESS = json["AUTO_BRIGHTNESS"];
    BRIGHTNESS = json["BRIGHTNESS"];
    UTC_OFFSET = json["UTC_OFFSET"];
    WUNDERGRROUND_API_KEY = json["WUNDERGRROUND_API_KEY"];
    WUNDERGRROUND_LANGUAGE = json["WUNDERGRROUND_LANGUAGE"];
    WUNDERGROUND_ZMW_CODE= json["WUNDERGROUND_ZMW_CODE"];

    String JS;
    json.printTo(JS);
    return JS;
}

void restoreSettings() {
    SPIFFS.remove("/config.json");
    Serial.println("Settings restored");
    ESP.restart();
    delay(1000);
}


void parsesettings(char json[]) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
    }

    if (root.containsKey("BRIGHTNESS")) BRIGHTNESS = root["BRIGHTNESS"];
    if (root.containsKey("SHOW_IP_ON_BOOT")) SHOW_IP_ON_BOOT = root["SHOW_IP_ON_BOOT"];
    if (root.containsKey("AUTO_BRIGHTNESS")) AUTO_BRIGHTNESS = root["AUTO_BRIGHTNESS"];
    if (root.containsKey("UTC_OFFSET")) UTC_OFFSET = root["UTC_OFFSET"];
    if (root.containsKey("WUNDERGRROUND_API_KEY")) WUNDERGRROUND_API_KEY = root["WUNDERGRROUND_API_KEY"];
    if (root.containsKey("WUNDERGRROUND_LANGUAGE")) WUNDERGRROUND_LANGUAGE = root["WUNDERGRROUND_LANGUAGE"];
    if (root.containsKey("WUNDERGROUND_ZMW_CODE")) WUNDERGROUND_ZMW_CODE = root["WUNDERGROUND_ZMW_CODE"];
    saveConfig();
}

bool saveConfig() {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["SHOW_IP_ON_BOOT"] = SHOW_IP_ON_BOOT;
    json["AUTO_BRIGHTNESS"] = AUTO_BRIGHTNESS;
    json["BRIGHTNESS"] = BRIGHTNESS;
    json["UTC_OFFSET"] = UTC_OFFSET;
    json["WUNDERGRROUND_API_KEY"] = WUNDERGRROUND_API_KEY;
    json["WUNDERGRROUND_LANGUAGE"] = WUNDERGRROUND_LANGUAGE;
    json["WUNDERGROUND_ZMW_CODE"] = WUNDERGROUND_ZMW_CODE;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
        Serial.println("Failed to open config file for writing");
        return false;
    }

    json.printTo(configFile);
    configFile.close();
    Serial.println("Config file saved");
    loadConfig();
    delay(500);
    return true;
}
