#ifndef MQTT_h
#define MQTT_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MQTT
{
    private:
        WiFiClient espClient;
        PubSubClient mqttClient;

    public:
        MQTT() : mqttClient(espClient) {};
        void setup();
        void loop();
};

#endif
