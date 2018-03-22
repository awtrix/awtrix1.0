#include <Arduino.h>
#include <ApplicationManager.h>
#include <AwtrixWiFi.h>
#include <OverTheAirUpdate.h>
#include <Settings.h>
#include <MQTT.h>
#include <DisplayManager.h>
#include <AwtrixBlynk.h>
#include <AwtrixSound.h>
#include "../lib/Awtrix/config.h"

#define BUTTON_RESET_CONFIG  D3

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
AwtrixBlynk ESPblynk;
AwtrixSound sound;
ApplicationManager& applications = ApplicationManager::getInstance();
AwtrixSettings& settings = AwtrixSettings::getInstance();

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_RESET_CONFIG, INPUT);
    settings.loadSPIFFS();
    wifi.setup();

    if (SETTINGS_FOUND){
    ota.setup();
        if (MQTT_ACTIVE) mqtt.setup();
        if (BLYNK_ACTIVE) ESPblynk.setup();
        if (FIRE_ACTIVE) applications.addApplication("Fire");
        if (TIME_ACTIVE) applications.addApplication("Time");
        if (WEATHER_ACTIVE) applications.addApplication("Weather");
        if (GOL_ACTIVE) applications.addApplication("Gol");
        if (YT_ACTIVE) applications.addApplication("Youtube");
        if (PET_ACTIVE) applications.addApplication("Pet");
        if (DHT_ACTIVE) applications.addApplication("DHT22");
        if (FB_ACTIVE) applications.addApplication("Facebook");
        if (SOUND) sound.setup();
    }else{
        DisplayManager::getInstance().setERR();
    }
    
}

void loop() {
    ota.loop();

    if (!ota.isUpdating()) {
        wifi.loop();
        if (MQTT_ACTIVE) mqtt.loop();
        applications.loop();
        if (BLYNK_ACTIVE)ESPblynk.loop();
        if (AUTO_BRIGHTNESS) DisplayManager::getInstance().checkLight();
    }
}


