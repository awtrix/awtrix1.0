#ifndef AwtrixWiFi_h
#define AwtrixWiFi_h

#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPUpdateServer.h>

class AwtrixWiFi
{
    private:
        void tcpLoop();

        ESP8266WebServer webserver;
        
        String address;

    public:
        AwtrixWiFi() : webserver(80) {};
        void setup();
        void loop();

};

#endif
