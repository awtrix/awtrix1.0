#ifndef AwtrixMQTT_h
#define AwtrixMQTT_h


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"


class MQTT
{
    private:        
        WiFiClient espClient;
        PubSubClient mqttClient;
        void commands(String, String);
        bool reconnect();
    public:
        MQTT() : mqttClient(espClient) {};
        int publish(char*,char*);
        void setup();
        void loop();
};

#endif