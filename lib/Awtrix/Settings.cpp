#include <Settings.h>
#include "FS.h"
#include "config.h"
#include <DisplayManager.h>

void AwtrixSettings::loadSPIFFS() {
    loadSettings();
    loadConfig();
}

String ICACHE_FLASH_ATTR AwtrixSettings::loadSettings() {
     if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
    }

    File setFile = SPIFFS.open(settingsFile, "r");
    if (!setFile) {
        SETTINGS_FOUND=0;
        Serial.println("Settings file not found!");
        return "";
    }

    size_t size = setFile.size();
    Serial.println(size);
    if (size > 2048) {
        Serial.println("Settings file size is too large");
    }
    Serial.println("Settings file loaded");
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);
    setFile.readBytes(buf.get(), size);
    setFile.close();
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf.get());

    if (!json.success()) {
        Serial.println("Failed to parse settings file");
        SETTINGS_FOUND=0; 
        return "";
    }

    SETTINGS_FOUND=1;

    MATRIX_MODE = json["MATRIX_MODE"];
    SHOW_IP_ON_BOOT= json["SHOW_IP_ON_BOOT"];
    ALEXA_ACTIVE = json["ALEXA_ACTIVE"];
    AUTO_BRIGHTNESS = json["AUTO_BRIGHTNESS"];
    BRIGHTNESS = json["BRIGHTNESS"];
    SHOW_WEEKDAY = json["SHOW_WEEKDAY"];
    UTC_OFFSET = json["UTC_OFFSET"];
    BIG_TIME = json["BIG_TIME"];
    PET_MOOD = json["PET_MOOD"];
    TEXT_COLOR_R = json["TEXT_COLOR_R"];
    TEXT_COLOR_G = json["TEXT_COLOR_G"];
    TEXT_COLOR_B = json["TEXT_COLOR_B"];
    RAINBOW = json["RAINBOW"];
    SCROLL_SPEED = json["SCROLL_SPEED"];
    AUTO_UPDATE = json["AUTO_UPDATE"];
    SOUND = json["SOUND"];
    BLYNK_ACTIVE= json["BLYNK_ACTIVE"];
    WEATHER_ACTIVE = json["WEATHER_ACTIVE"];
    WEATHERHUM_ACTIVE = json["WEATHERHUM_ACTIVE"];
    GOL_ACTIVE = json["GOL_ACTIVE"];
    PET_ACTIVE = json["PET_ACTIVE"];
    FB_ACTIVE = json["FB_ACTIVE"];
    YT_ACTIVE = json["YT_ACTIVE"];
    TWITTER_ACTIVE = json["TWITTER_ACTIVE"];
    DHT_ACTIVE = json["DHT_ACTIVE"];
    FIRE_ACTIVE = json["FIRE_ACTIVE"];
    APP_DURATION = json["APP_DURATION"];
    MQTT_ACTIVE= json["MQTT_ACTIVE"];
    SLEEP_START_MIN = json["SLEEP_START_MIN"];
    SLEEP_START_HR = json["SLEEP_START_HR"];
    SLEEP_STOP_MIN = json["SLEEP_STOP_MIN"];
    SLEEP_STOP_HR= json["SLEEP_STOP_HR"];
    SLEEP_MODE_ACTIVE = json["SLEEP_MODE_ACTIVE"];

    String JS;
    json.printTo(JS);
    return JS;
}

void ICACHE_FLASH_ATTR AwtrixSettings::loadConfig() {
     if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
    }

    File confFile = SPIFFS.open(configFile, "r");
    if (!confFile) {
        Serial.println("Config File not found!");
        SETTINGS_FOUND=0;
        
        return;
    }

    size_t size = confFile.size();
    if (size > 2048) {
        Serial.println("Config file size is too large");
    }
    Serial.println("Config file loaded");
    std::unique_ptr<char[]> buf(new char[size]);
    confFile.readBytes(buf.get(), size);
    confFile.close();
    DynamicJsonBuffer jsonBuffer(bufferSize);
    JsonObject& json = jsonBuffer.parseObject(buf.get());

    if (!json.success()) {
        Serial.println("Failed to parse config file");
        SETTINGS_FOUND=0;
        return;
    }

if (json.containsKey("OWM_API_KEY")){
    OWM_API_KEY = (char*)malloc(json["OWM_API_KEY"].measureLength()+1);
    OWM_API_KEY[0] = '\0';
    strcpy(OWM_API_KEY, (const char*)json["OWM_API_KEY"]);
}else{
    WEATHER_ACTIVE=0;
}


if (json.containsKey("OWM_LOCATION")){
    OWM_LOCATION = (char*)malloc(json["OWM_LOCATION"].measureLength()+1);
    OWM_LOCATION[0] = '\0';
    strcpy(OWM_LOCATION, (const char*)json["OWM_LOCATION"]);
}else{
    WEATHER_ACTIVE=0;
}

if (json.containsKey("YT_API_KEY")){
    YT_API_KEY = (char*)malloc(json["YT_API_KEY"].measureLength()+1);
    YT_API_KEY[0] = '\0';
    strcpy(YT_API_KEY, (const char*)json["YT_API_KEY"]);
}else{
    YT_ACTIVE=0;
}

if (json.containsKey("YT_CHANNEL_ID")){
    YT_CHANNEL_ID = (char*)malloc(json["YT_CHANNEL_ID"].measureLength()+1);
    YT_CHANNEL_ID[0] = '\0';
    strcpy(YT_CHANNEL_ID, (const char*)json["YT_CHANNEL_ID"]);
}else{
    YT_ACTIVE=0;
}

if (json.containsKey("TWITTER_PROFILE")){
    TWITTER_PROFILE = (char*)malloc(json["TWITTER_PROFILE"].measureLength()+1);
    TWITTER_PROFILE[0] = '\0';
    strcpy(TWITTER_PROFILE, (const char*)json["TWITTER_PROFILE"]);
}else{
    TWITTER_ACTIVE=0;
}

if (json.containsKey("FB_API_URL")){
    FB_API_URL = (char*)malloc(json["FB_API_URL"].measureLength()+1);
    FB_API_URL[0] = '\0';
    strcpy(FB_API_URL, (const char*)json["FB_API_URL"]);
}else{
    FB_ACTIVE=0;
}

if (json.containsKey("FINGERPRINT")){
    FINGERPRINT = (char*)malloc(json["FINGERPRINT"].measureLength()+1);
    FINGERPRINT[0] = '\0';
    strcpy(FINGERPRINT, (const char*)json["FINGERPRINT"]);
}else{
    FB_ACTIVE=0;
}

if (json.containsKey("MQTT_SERVER")){
    MQTT_SERVER = (char*)malloc(json["MQTT_SERVER"].measureLength()+1);
    MQTT_SERVER[0] = '\0';
    strcpy(MQTT_SERVER, (const char*)json["MQTT_SERVER"]);
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("MQTT_USERNAME")){
    MQTT_USERNAME = (char*)malloc(json["MQTT_USERNAME"].measureLength()+1);
    MQTT_USERNAME[0] = '\0';
    strcpy(MQTT_USERNAME, (const char*)json["MQTT_USERNAME"]);
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("MQTT_PASSWORD")){
    MQTT_PASSWORD = (char*)malloc(json["MQTT_PASSWORD"].measureLength()+1);
    MQTT_PASSWORD[0] = '\0';
    strcpy(MQTT_PASSWORD, (const char*)json["MQTT_PASSWORD"]);
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("MQTT_PORT")){
    MQTT_PORT = json["MQTT_PORT"];
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("BLYNK_KEY")){
    BLYNK_KEY = (char*)malloc(json["BLYNK_KEY"].measureLength()+1);
    BLYNK_KEY[0] = '\0';
    strcpy(BLYNK_KEY, (const char*)json["BLYNK_KEY"]);
    }else{
        BLYNK_ACTIVE=0;
    }
}

bool ICACHE_FLASH_ATTR AwtrixSettings::saveSettings() {
     StaticJsonBuffer<800> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["MATRIX_MODE"] = MATRIX_MODE;
    json["SHOW_IP_ON_BOOT"] = SHOW_IP_ON_BOOT;
    json["ALEXA_ACTIVE"] = ALEXA_ACTIVE;
    json["AUTO_BRIGHTNESS"] = AUTO_BRIGHTNESS;
    json["BRIGHTNESS"] = BRIGHTNESS;
    json["SHOW_WEEKDAY"] = SHOW_WEEKDAY;
    json["UTC_OFFSET"] = UTC_OFFSET;
    json["BIG_TIME"] = BIG_TIME;
    json["PET_MOOD"] = PET_MOOD;
    json["TEXT_COLOR_R"] = TEXT_COLOR_R;
    json["TEXT_COLOR_G"] = TEXT_COLOR_G;
    json["TEXT_COLOR_B"] = TEXT_COLOR_B;
    json["RAINBOW"] = RAINBOW;
    json["SCROLL_SPEED"] = SCROLL_SPEED;
    json["AUTO_UPDATE"] = AUTO_UPDATE;
    json["SOUND"] = SOUND;
    json["WEATHER_ACTIVE"] = WEATHER_ACTIVE;
    json["TWITTER_ACTIVE"] = TWITTER_ACTIVE;
    json["GOL_ACTIVE"] = GOL_ACTIVE;
    json["PET_ACTIVE"] = PET_ACTIVE;
    json["FB_ACTIVE"] = FB_ACTIVE;
    json["YT_ACTIVE"] = YT_ACTIVE;
    json["DHT_ACTIVE"] = DHT_ACTIVE;
    json["FIRE_ACTIVE"] = FIRE_ACTIVE;
    json["MQTT_ACTIVE"] = MQTT_ACTIVE;
    json["BLYNK_ACTIVE"] = BLYNK_ACTIVE;
    json["APP_DURATION"] = APP_DURATION;
    json["SLEEP_START_MIN"] = SLEEP_START_MIN;
    json["SLEEP_START_HR"] = SLEEP_START_HR;
    json["SLEEP_STOP_MIN"] = SLEEP_STOP_MIN;
    json["SLEEP_STOP_HR"] = SLEEP_STOP_HR;
    json["SLEEP_MODE_ACTIVE"] = SLEEP_MODE_ACTIVE;

    File setFile = SPIFFS.open(settingsFile, "w");
    if (!setFile) {
        Serial.println("Failed to open Settings file for writing");
        return false;
    }

    json.printTo(setFile);
    setFile.close();
    Serial.println("Settings file saved");
 
    return true;
}


void ICACHE_FLASH_ATTR AwtrixSettings::parseSettings(String json) {
   Serial.println("Got Settings"); 
    StaticJsonBuffer<1000> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
    }

    if (root.containsKey("MATRIX_MODE"))  MATRIX_MODE = root["MATRIX_MODE"];
    if (root.containsKey("SHOW_IP_ON_BOOT"))  SHOW_IP_ON_BOOT = root["SHOW_IP_ON_BOOT"];
    if (root.containsKey("ALEXA_ACTIVE"))  ALEXA_ACTIVE = root["ALEXA_ACTIVE"];
    if (root.containsKey("AUTO_BRIGHTNESS"))  AUTO_BRIGHTNESS = root["AUTO_BRIGHTNESS"];
    if (root.containsKey("BRIGHTNESS"))  BRIGHTNESS = root["BRIGHTNESS"];
    if (root.containsKey("SHOW_WEEKDAY"))  SHOW_WEEKDAY = root["SHOW_WEEKDAY"];
    if (root.containsKey("UTC_OFFSET"))  UTC_OFFSET = root["UTC_OFFSET"];
    if (root.containsKey("BIG_TIME"))  BIG_TIME = root["BIG_TIME"];
    if (root.containsKey("PET_MOOD"))  PET_MOOD = root["PET_MOOD"];
    if (root.containsKey("TEXT_COLOR_R"))  TEXT_COLOR_R = root["TEXT_COLOR_R"];
    if (root.containsKey("TEXT_COLOR_G"))  TEXT_COLOR_G = root["TEXT_COLOR_G"];
    if (root.containsKey("TEXT_COLOR_B"))  TEXT_COLOR_B = root["TEXT_COLOR_B"];
    if (root.containsKey("RAINBOW"))  RAINBOW = root["RAINBOW"];
    if (root.containsKey("SCROLL_SPEED"))  SCROLL_SPEED = root["SCROLL_SPEED"];
    if (root.containsKey("AUTO_UPDATE"))  AUTO_UPDATE = root["AUTO_UPDATE"];
    if (root.containsKey("SOUND"))  SOUND = root["SOUND"];
    if (root.containsKey("WEATHER_ACTIVE"))  WEATHER_ACTIVE = root["WEATHER_ACTIVE"];
    if (root.containsKey("TWITTER_ACTIVE"))  TWITTER_ACTIVE = root["TWITTER_ACTIVE"];
    if (root.containsKey("GOL_ACTIVE"))  GOL_ACTIVE = root["GOL_ACTIVE"];
    if (root.containsKey("PET_ACTIVE"))  PET_ACTIVE = root["PET_ACTIVE"];
    if (root.containsKey("FB_ACTIVE"))  FB_ACTIVE = root["FB_ACTIVE"];
    if (root.containsKey("YT_ACTIVE"))  YT_ACTIVE = root["YT_ACTIVE"];
    if (root.containsKey("DHT_ACTIVE"))  DHT_ACTIVE = root["DHT_ACTIVE"];
    if (root.containsKey("FIRE_ACTIVE"))  FIRE_ACTIVE = root["FIRE_ACTIVE"];
    if (root.containsKey("MQTT_ACTIVE"))  MQTT_ACTIVE = root["MQTT_ACTIVE"];
    if (root.containsKey("BLYNK_ACTIVE"))  BLYNK_ACTIVE = root["BLYNK_ACTIVE"];
    if (root.containsKey("APP_DURATION"))  APP_DURATION = root["APP_DURATION"];
    if (root.containsKey("SLEEP_START_MIN"))  SLEEP_START_MIN = root["SLEEP_START_MIN"];
    if (root.containsKey("SLEEP_START_HR"))  SLEEP_START_HR = root["SLEEP_START_HR"];
    if (root.containsKey("SLEEP_STOP_MIN"))  SLEEP_STOP_MIN = root["SLEEP_STOP_MIN"];
    if (root.containsKey("SLEEP_STOP_HR"))  SLEEP_STOP_HR = root["SLEEP_STOP_HR"];
    if (root.containsKey("SLEEP_MODE_ACTIVE"))  SLEEP_MODE_ACTIVE = root["SLEEP_MODE_ACTIVE"];
    saveSettings();
}
