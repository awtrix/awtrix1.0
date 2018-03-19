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
    BIG_TIME = json["BIG_TIME"];
    PET_MOOD = json["PET_MOOD"];
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
    json["BIG_TIME"] = BIG_TIME;
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
    if (root.containsKey("BIG_TIME"))    BIG_TIME = root["BIG_TIME"];
    if (root.containsKey("PET_MOOD"))  PET_MOOD = root["PET_MOOD"];
    if (root.containsKey("AUTO_UPDATE")) AUTO_UPDATE = root["AUTO_UPDATE"];
    if (root.containsKey("TEXT_COLOR_R")) TEXT_COLOR_R = root["TEXT_COLOR_R"];
    if (root.containsKey("TEXT_COLOR_G")) TEXT_COLOR_G = root["TEXT_COLOR_G"];
    if (root.containsKey("TEXT_COLOR_B")) TEXT_COLOR_B = root["TEXT_COLOR_B"];
    if (root.containsKey("SCROLL_SPEED")) SCROLL_SPEED = root["SCROLL_SPEED"];
    saveSettings();
}
