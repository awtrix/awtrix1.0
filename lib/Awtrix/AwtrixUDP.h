#ifndef AwtrixUDP_h
#define AwtrixUDP_h
#include <AwtrixWiFi.h>
#include <AwtrixBroker.h>


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
