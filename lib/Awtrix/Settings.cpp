#include <Settings.h>
#include "FS.h"
#include "config.h"


void AwtrixSettings::loadSettings() {
     if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
    }

    File configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
        Serial.println("Writing default Settings");
        saveSettings();
    }

    size_t size = configFile.size();
    Serial.println(size);
    if (size > 2048) {
        Serial.println("Config file size is too large");
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
    }

    SHOW_IP_ON_BOOT= json["SHOW_IP_ON_BOOT"];
    AUTO_BRIGHTNESS = json["AUTO_BRIGHTNESS"];
    BRIGHTNESS = json["BRIGHTNESS"];
    UTC_OFFSET = json["UTC_OFFSET"];
    WUNDERGROUND_API_KEY = json["WUNDERGRROUND_API_KEY"];
    WUNDERGROUND_LANGUAGE = json["WUNDERGRROUND_LANGUAGE"];
    WUNDERGROUND_ZMW_CODE= json["WUNDERGROUND_ZMW_CODE"];
    MQTT_SERVER= json["MQTT_SERVER"];
    MQTT_PORT= json["MQTT_PORT"];
    MQTT_USERNAME= json["MQTT_USERNAME"];
    MQTT_PASSWORD= json["MQTT_PASSWORD"];
    BLYNK_KEY= json["BLYNK_KEY"];
    BIG_TIME = json["BIG_TIME"];
    PET_MOOD = json["PET_MOOD"];
    YT_API_KEY = json["YT_API_KEY"];
    YT_CHANNEL_ID = json["YT_CHANNEL_ID"];
    FB_API_URL = json["FB_API_URL"];
    FINGERPRINT = json["FINGERPRINT"];
    AUTO_UPDATE = json["AUTO_UPDATE"];
    TEXT_COLOR_R = json["TEXT_COLOR_R"];
    TEXT_COLOR_G = json["TEXT_COLOR_G"];
    TEXT_COLOR_B = json["TEXT_COLOR_B"];
    SCROLL_SPEED = json["SCROLL_SPEED"];
}

bool AwtrixSettings::saveSettings() {
     StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["SHOW_IP_ON_BOOT"] = SHOW_IP_ON_BOOT;
    json["AUTO_BRIGHTNESS"] = AUTO_BRIGHTNESS;
    json["BRIGHTNESS"] = BRIGHTNESS;
    json["UTC_OFFSET"] = UTC_OFFSET;
    json["WUNDERGRROUND_API_KEY"] = WUNDERGROUND_API_KEY;
    json["WUNDERGRROUND_LANGUAGE"] = WUNDERGROUND_LANGUAGE;
    json["WUNDERGROUND_ZMW_CODE"] = WUNDERGROUND_ZMW_CODE;
    json["MQTT_SERVER"] = MQTT_SERVER;
    json["MQTT_PORT"] = MQTT_PORT;
    json["MQTT_USERNAME"] = MQTT_USERNAME;
    json["MQTT_PASSWORD"] = MQTT_PASSWORD;
    json["BLYNK_KEY"] = BLYNK_KEY;
    json["BIG_TIME"] = BIG_TIME;
    json["PET_MOOD"] = PET_MOOD;
    json["YT_API_KEY"] = YT_API_KEY;
    json["YT_CHANNEL_ID"] = YT_CHANNEL_ID;
    json["FB_API_URL"] = FB_API_URL;
    json["FINGERPRINT"] = FINGERPRINT;
    json["AUTO_UPDATE"] = AUTO_UPDATE;
    json["TEXT_COLOR_R"] = TEXT_COLOR_R ;
    json["TEXT_COLOR_G"] = TEXT_COLOR_G ;
    json["TEXT_COLOR_B"] = TEXT_COLOR_B;
    json["SCROLL_SPEED"] = SCROLL_SPEED ;


    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {

        Serial.println("Failed to open config file for writing");
        return false;
    }

    json.printTo(configFile);
    configFile.close();
    Serial.println("Config file saved");

    loadSettings();
    delay(500);
    return true;
}

void AwtrixSettings::restoreSettings() {
    SPIFFS.remove("/config.json");
    Serial.println("Settings restored");
    ESP.restart();
    delay(1000);
}

void AwtrixSettings::parseSettings(String json) {
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
    if (root.containsKey("WUNDERGRROUND_API_KEY")) WUNDERGROUND_API_KEY = root["WUNDERGRROUND_API_KEY"];
    if (root.containsKey("WUNDERGRROUND_LANGUAGE")) WUNDERGROUND_LANGUAGE = root["WUNDERGRROUND_LANGUAGE"];
    if (root.containsKey("WUNDERGROUND_ZMW_CODE")) WUNDERGROUND_ZMW_CODE = root["WUNDERGROUND_ZMW_CODE"];
    if (root.containsKey("MQTT_SERVER")) MQTT_SERVER = root["MQTT_SERVER"];
    if (root.containsKey("MQTT_PORT")) MQTT_PORT = root["MQTT_PORT"];
    if (root.containsKey("MQTT_USERNAME")) WUNDERGROUND_ZMW_CODE = root["MQTT_USERNAME"];
    if (root.containsKey("MQTT_PASSWORD")) WUNDERGROUND_ZMW_CODE = root["MQTT_PASSWORD"];
    if (root.containsKey("BLYNK_KEY")) WUNDERGROUND_ZMW_CODE = root["BLYNK_KEY"];
    if (root.containsKey("BIG_TIME"))    BIG_TIME = root["BIG_TIME"];
    if (root.containsKey("PET_MOOD"))  PET_MOOD = root["PET_MOOD"];
    if (root.containsKey("YT_API_KEY")) YT_API_KEY = root["YT_API_KEY"];
    if (root.containsKey("YT_CHANNEL_ID")) YT_CHANNEL_ID = root["YT_CHANNEL_ID"];
    if (root.containsKey("FB_API_URL")) FB_API_URL = root["FB_API_URL"];
    if (root.containsKey("FINGERPRINT")) FINGERPRINT = root["FINGERPRINT"];
    if (root.containsKey("AUTO_UPDATE")) AUTO_UPDATE = root["AUTO_UPDATE"];
    if (root.containsKey("TEXT_COLOR_R")) TEXT_COLOR_R = root["TEXT_COLOR_R"];
    if (root.containsKey("TEXT_COLOR_G")) TEXT_COLOR_G = root["TEXT_COLOR_G"];
    if (root.containsKey("TEXT_COLOR_B")) TEXT_COLOR_B = root["TEXT_COLOR_B"];
    if (root.containsKey("SCROLL_SPEED")) SCROLL_SPEED = root["SCROLL_SPEED"];
    saveSettings();
}
