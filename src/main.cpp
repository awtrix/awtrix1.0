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
#include <TimeClient.h>

TimeClient timeClient1(UTC_OFFSET);

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
AwtrixBlynk ESPblynk;
AwtrixSound sound;
ApplicationManager& applications = ApplicationManager::getInstance();
AwtrixSettings& settings = AwtrixSettings::getInstance();

void setup() {
    Serial.begin(115200);
    Serial1.begin(9800);
    settings.loadSPIFFS();
    wifi.setup();

    if (SETTINGS_FOUND){
    ota.setup();
        if (MQTT_ACTIVE) mqtt.setup();
        if (BLYNK_ACTIVE) ESPblynk.setup();
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

void checkSleepMode(){
    if (timeClient1.getHours().toInt() == SLEEP_START_HR & timeClient1.getMinutes().toInt() == SLEEP_START_MIN){
        SLEEP_MODE=1;
    }
    if (timeClient1.getHours().toInt() == SLEEP_STOP_HR & timeClient1.getMinutes().toInt() == SLEEP_STOP_MIN){
        SLEEP_MODE=0;
    }
}


long pMillis = 0; 
void loop() {
    ota.loop();

    if (!ota.isUpdating()) {
        wifi.loop();
        if (MQTT_ACTIVE) mqtt.loop();
        if (SETTINGS_FOUND) applications.loop();
        if (BLYNK_ACTIVE)ESPblynk.loop();
        if (AUTO_BRIGHTNESS) DisplayManager::getInstance().checkLight();
        if(millis() - pMillis > 30000) {
        if (SETTINGS_FOUND) timeClient1.updateTime();    
        pMillis = millis();  
        checkSleepMode();
        }
    }
}


