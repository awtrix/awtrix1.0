#include <OverTheAirUpdate.h>
#include <DisplayManager.h>
#include <ArduinoOTA.h>

void OverTheAirUpdate::setup() {
    Serial.println("Setup OTA");

    ArduinoOTA.onStart([&]() {
        Serial.println("OTA Start");
        updating = true;

        DisplayManager::getInstance().clear();
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        // DisplayManager::getInstance().loading(progress, total);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);

        switch (error) {
            case OTA_AUTH_ERROR:
                Serial.println("Auth failed");
                break;
            case OTA_BEGIN_ERROR:
                Serial.println("Begin failed");
                break;
            case OTA_CONNECT_ERROR:
                Serial.println("Connect failed");
                break;
            case OTA_RECEIVE_ERROR:
                Serial.println("Receive failed");
                break;
            case OTA_END_ERROR:
                Serial.println("End failed");
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
