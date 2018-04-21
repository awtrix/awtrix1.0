#ifndef AwtrixMQTT_h
#define AwtrixMQTT_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include <AwtrixBroker.h>

class MQTT
{
    private:        
        bool reconnect();
    public:
        static MQTT& getInstance() {
            static MQTT instance;
            return instance;
        }
        void sendLog(String);
        void setup();
        void loop();

};


    

#endif