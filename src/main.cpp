#include <Arduino.h>
#include <AwtrixMatrix.h>
#include <AwtrixWiFi.h>
#include <OverTheAirUpdate.h>
#include <MQTT.h>

#define BUTTON_RESET_CONFIG  D3

OverTheAirUpdate ota;
AwtrixWiFi wifi;
MQTT mqtt;
AwtrixMatrix& matrix = AwtrixMatrix::getInstance();

void setup() {
    Serial.begin(115200);

    pinMode(BUTTON_RESET_CONFIG, INPUT);

    ota.setup();
    wifi.setup();
    mqtt.setup();

    /*
    loadConfig();
    soundSetup();
    Serial.println("Awtrix successfully started");
    if (ENABLE_HEARTBEAT) {
        setupHeartbeat();
    }
    setupTimeUpdate();
    weatherUpdate();
    getYTSubs(YTchannel);
    */
}

void loop() {
    ota.loop();

    if (!ota.isUpdating()) {
        wifi.loop();
        mqtt.loop();
    }
}

/*
#include <EEPROM.h>
#include <stdint.h>
#include "config.h"

bool GOL;
bool NOTIFICATION;
bool TIME;
bool WEATHER;
bool PET;
bool OTA;
int  PET_MOOD = 1;
unsigned long previousMillis = 0;
const long interval = 1000; 

const unsigned long Minutes = 1 * 1 * 1000UL;
static unsigned long lastSampleTime = 0 - Minutes;

void loop() {
    if (!GOL && !PET && !WEATHER && !NOTIFICATION) {
        unsigned long now = millis();
        if (now - lastSampleTime >= Minutes)
        {
            lastSampleTime += Minutes;
            showTime();
        }
    }

    if (PET && !GOL && !WEATHER && !NOTIFICATION) vPetLoop();

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