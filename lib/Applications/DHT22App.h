#ifndef AwtrixDHT22Application_h
#define AwtrixDHT22Application_h

#include <IApplication.h>
#include "DHT.h"

class DHT22App : public IApplication
{
    private:
        int humidity;
        int temperature;
        DHT dht;
        
        const unsigned long UpdateThreshold = 160000l;
    public:
        DHT22App();    
        void render(DisplayManager&) override;
        void update() override;
};

#endif
