#include <Arduino.h>
#include <ApplicationManager.h>
#include <AwtrixWiFi.h>
#include <OverTheAirUpdate.h>
#include <Settings.h>
#include <MQTT.h>
#include <DisplayManager.h>
#include <AwtrixBlynk.h>

#define BUTTON_RESET_CONFIG  D3

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
AwtrixBlynk ESPblynk;
ApplicationManager& applications = ApplicationManager::getInstance();

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_RESET_CONFIG, INPUT);

    wifi.setup();
    mqtt.setup();
    ota.setup();
    ESPblynk.setup();
//Activate or deactivate  Apps:

   
    applications.addApplication("Time");
    applications.addApplication("Weather");
    applications.addApplication("Gol");
    applications.addApplication("Youtube");
    applications.addApplication("Pet");
    applications.addApplication("DHT22");
    applications.addApplication("Facebook");

}

void loop() {
    ota.loop();

    if (!ota.isUpdating()) {
        wifi.loop();
        mqtt.loop();
        applications.loop();
        ESPblynk.loop();
        //DisplayManager::getInstance().checkLight();
    }
}


