#ifndef AwtrixWiFi_h
#define AwtrixWiFi_h

#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WiFiClientSecure.h>
#include <fauxmoESP.h>


class AwtrixWiFi
{
    private:
        fauxmoESP alexa;
        WiFiClientSecure client;
        String address;

    public:

        void setup();
        void loop();
       
};

#endif
