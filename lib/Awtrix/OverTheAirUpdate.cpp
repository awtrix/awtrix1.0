#include <OverTheAirUpdate.h>
#include <DisplayManager.h>
#include <ArduinoOTA.h>

void OverTheAirUpdate::setup() {

    ArduinoOTA.onStart([&]() {
        Serial.println(F("OTA Start"));
        updating = true;

        DisplayManager::getInstance().clear();
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
         DisplayManager::getInstance().flashProgress(progress, total);
    });

    ArduinoOTA.begin();
}

bool OverTheAirUpdate::isUpdating() {
    return updating;
}

void OverTheAirUpdate::loop() {
    ArduinoOTA.handle();
}
