#ifndef AwtrixUDP_h
#define AwtrixUDP_h
#include <AwtrixWiFi.h>
#include "config.h"
#include <DisplayManager.h>
#include <Settings.h>
#include <ApplicationManager.h>

class AwtrixUDP
{
    private:
        WiFiUDP Udp;

    public:
        void setup();
        void loop();
        void sendMSG(String);
};

#endif
