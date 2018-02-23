#ifndef AwtrixDHT22Application_h
#define AwtrixDHT22Application_h

#include <IApplication.h>
#include "DHT.h"

class DHT22App : public IApplication
{
    private:
        float humidity;
        float temperature;
        DHT dht;
        
    public:
        DHT22App();    
        void render(DisplayManager&) override;
        void update() override;
};

#endif
