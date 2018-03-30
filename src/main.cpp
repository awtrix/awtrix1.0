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
#include <timeLib.h>

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
NTP NTPclient;
AwtrixBlynk ESPblynk;
AwtrixSound sound;
ApplicationManager& applications = ApplicationManager::getInstance();
AwtrixSettings& settings = AwtrixSettings::getInstance();

time_t NTPgetTime()
{
return NTPclient.getNtpTime();
}

void setup() {
    Serial.begin(115200);
    Serial.print("AWTRIX START");
    settings.loadSPIFFS();
    if (MATRIX_MODE) DisplayManager::getInstance().setLayout();
    wifi.setup();
    ota.setup();
    if (SETTINGS_FOUND){
        
        NTPclient.begin("0.pool.ntp.org",UTC_OFFSET);
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
        getExternalTime t = NTPgetTime;
        setSyncProvider(t);
        setSyncInterval(60);
    }else{
        DisplayManager::getInstance().setERR();
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
            if (SLEEP_MODE_ACTIVE) NTPclient.checkSleepMode();
            }
        }
    }


