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
#include <AwtrixUDP.h>

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
AwtrixUDP udp;
AwtrixBlynk ESPblynk;
AwtrixSound sound;
ApplicationManager& applications = ApplicationManager::getInstance();
AwtrixSettings& settings = AwtrixSettings::getInstance();

void setup() {
ESP.wdtDisable();
ESP.wdtEnable(WDTO_8S);
    Serial.begin(115200);
    Serial1.begin(9800);
    settings.loadSPIFFS();
    if (MATRIX_MODE) DisplayManager::getInstance().setLayout();
    DisplayManager::getInstance().showBoot();
    wifi.setup();
    ota.setup();
    udp.setup();
    if (SETTINGS_FOUND){
            applications.loadDefault();
        if (MQTT_ACTIVE) mqtt.setup();
        if (BLYNK_ACTIVE) ESPblynk.setup();
        if (WEATHER_ACTIVE) applications.addApplication("Weather");
        if (TWITTER_ACTIVE) applications.addApplication("Twitter");
        if (GOL_ACTIVE) applications.addApplication("Gol");
        if (YT_ACTIVE) applications.addApplication("Youtube");
        if (PET_ACTIVE) applications.addApplication("Pet");
        if (DHT_ACTIVE) applications.addApplication("DHT22");
        if (FB_ACTIVE) applications.addApplication("Facebook");
        if (FIRE_ACTIVE) applications.addApplication("Fire");
        if (SOUND) sound.setup();
    }else{
        DisplayManager::getInstance().setERR();
    }
     
}

void loop() {
    ota.loop();
        if (!ota.isUpdating()) {
            wifi.loop();
            udp.loop();
            if (SETTINGS_FOUND) applications.loop();        
            if(!gamemode){
                if (MQTT_ACTIVE) mqtt.loop();
                if (BLYNK_ACTIVE) ESPblynk.loop();
                if (AUTO_BRIGHTNESS) DisplayManager::getInstance().checkLight();
            }   
    }
}


