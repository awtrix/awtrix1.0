#ifndef AwtrixWeatherApplication_h
#define AwtrixWeatherApplication_h

#include <IApplication.h>
#include <../Awtrix/config.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> 

class WeatherApp : public IApplication
{
    private:
        float temperature;
        float humidity;
        String description;
         String city;
     
    public:

        void render(DisplayManager&) override;
        void enable() override;

};

#endif
