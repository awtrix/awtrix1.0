#ifndef AwtrixWiFi_h
#define AwtrixWiFi_h

#include <WiFiManager.h>

class AwtrixWiFi
{
    private:
        void udpLoop();
        void tcpLoop();

        WiFiUDP udp;
        ESP8266WebServer webserver;
        String address;

    public:
        AwtrixWiFi();
        void setup();
        void loop();
};

#endif
