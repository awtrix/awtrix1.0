#include <OverTheAirUpdate.h>
#include <DisplayManager.h>
#include <ArduinoOTA.h>

void OverTheAirUpdate::setup() {
    

    ArduinoOTA.onStart([&]() {
        Serial.println(F("OTA Start"));
        updating = true;

        DisplayManager::getInstance().clear();
    });

    ArduinoOTA.onEnd([]() {
    
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
         DisplayManager::getInstance().flashProgress(progress, total);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);

        switch (error) {
            case OTA_AUTH_ERROR:
                Serial.println(F("Auth failed"));
                break;
            case OTA_BEGIN_ERROR:
                Serial.println(F("Begin failed"));
                break;
            case OTA_CONNECT_ERROR:
                Serial.println(F("Connect failed"));
                break;
            case OTA_RECEIVE_ERROR:
                Serial.println(F("Receive failed"));
                break;
            case OTA_END_ERROR:
                Serial.println(F("End failed"));
                break;
        }
    });

    ArduinoOTA.begin();
}

bool OverTheAirUpdate::isUpdating() {
    return updating;
}

void OverTheAirUpdate::loop() {
    ArduinoOTA.handle();
}
