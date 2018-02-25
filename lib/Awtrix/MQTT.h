#ifndef AwtrixMQTT_h
#define AwtrixMQTT_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Settings.h>

class MQTT
{
    private:
        AwtrixSettings& settings = AwtrixSettings::getInstance();
        
        WiFiClient espClient;
        PubSubClient mqttClient;

    public:
        MQTT() : mqttClient(espClient) {};
        int publish(char*,char*);
        void setup();
        void loop();
};

#endif
