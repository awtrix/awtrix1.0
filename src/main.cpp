#include <Arduino.h>
#include <ApplicationManager.h>
#include <AwtrixWiFi.h>
#include <OverTheAirUpdate.h>
#include <settings.h>
#include <MQTT.h>

#define BUTTON_RESET_CONFIG  D3

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
ApplicationManager& applications = ApplicationManager::getInstance();
AwtrixSettings& settings = AwtrixSettings::getInstance();

void setup() {
    Serial.begin(115200);

    pinMode(BUTTON_RESET_CONFIG, INPUT);

    wifi.setup();
    settings.initialise();
    settings.set("wundergroundLanguage","nl");
    Serial.println(settings.get<String>("wundergroundLanguage"));
    mqtt.setup();
    ota.setup();

    applications.addApplication("Time");
    applications.addApplication("Weather");
    applications.addApplication("Pet");
    //applications.addApplication("Plasma");
    applications.addApplication("Pet");
    //applications.addApplication("Youtube");
    applications.addApplication("DHT22");
    /*
    loadConfig();
    soundSetup();
    if (ENABLE_HEARTBEAT) {
        setupHeartbeat();
    }
    */
}

void loop() {
    ota.loop();

    if (!ota.isUpdating()) {
        wifi.loop();
        mqtt.loop();
        applications.loop();
    }
}

/*
void loop() {
    // This code probably belongs in the DisplayManager
    if (AUTO_BRIGHTNESS) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            checkLight();
        }
    } else {
        matrixBrightness(BRIGHTNESS);
    }
}
*/
