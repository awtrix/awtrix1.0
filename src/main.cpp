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
#include <NTP.h>
#include <TimeLib.h>

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
AwtrixBlynk ESPblynk;
AwtrixSound sound;
ApplicationManager& applications = ApplicationManager::getInstance();
AwtrixSettings& settings = AwtrixSettings::getInstance();


void setup() {
    Serial.begin(115200);
    Serial.print("AWTRIX START");
    DisplayManager::getInstance().showBoot();
    settings.loadSPIFFS();
    if (MATRIX_MODE) DisplayManager::getInstance().setLayout();
    wifi.setup();
    ota.setup();
    if (SETTINGS_FOUND){
        if (MQTT_ACTIVE) mqtt.setup();
        if (BLYNK_ACTIVE) ESPblynk.setup();
        applications.addApplication("Time");
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

   void checkSleepMode(){
    uint32_t now, start, stop;
      now = ((hour() * 3600) + (minute() * 60) + second());
      start = (SLEEP_START_HR * 3600) + (SLEEP_START_MIN * 60);
      stop = (SLEEP_STOP_HR * 3600) + (SLEEP_STOP_MIN * 60);

      if (start < stop) {
        SLEEP_MODE = (now >= start && now <= stop ) ? 1 : 0;
      } else {
        SLEEP_MODE = (now >= start || now <= stop) ? 1 : 0;
      }
}

void loop() {
    ota.loop();
    wifi.loop();   
    if (SETTINGS_FOUND){
        if (!ota.isUpdating()) {       
            if (MQTT_ACTIVE) mqtt.loop();
            if (SETTINGS_FOUND) applications.loop();
            if (BLYNK_ACTIVE)ESPblynk.loop();
            if (AUTO_BRIGHTNESS) DisplayManager::getInstance().checkLight(); 
            if (SLEEP_MODE_ACTIVE) checkSleepMode();
            }
        }
    }

