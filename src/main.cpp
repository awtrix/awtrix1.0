#include <Arduino.h>
#include <ApplicationManager.h>
#include <AwtrixWiFi.h>
#include <OverTheAirUpdate.h>
#include <settings.h>
#include <MQTT.h>
#include <DisplayManager.h>

#define BUTTON_RESET_CONFIG  D3

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
ApplicationManager& applications = ApplicationManager::getInstance();
AwtrixSettings& settings = AwtrixSettings::getInstance();

void setup() {
    Serial.begin(115200);
    settings.initialise();
    pinMode(BUTTON_RESET_CONFIG, INPUT);

    wifi.setup();
    mqtt.setup();
    ota.setup();

//Activate or deactivate  Apps:

    applications.addApplication("Time");
    applications.addApplication("Weather");
    //applications.addApplication("Gol");
    //applications.addApplication("Pet");
    //applications.addApplication("DHT22");
    //applications.addApplication("Youtube");
    //applications.addApplication("Facebook");
}

void loop() {
    ota.loop();

    if (!ota.isUpdating()) {
        wifi.loop();
        mqtt.loop();
        applications.loop();
        DisplayManager::getInstance().checkLight();
    }
}


