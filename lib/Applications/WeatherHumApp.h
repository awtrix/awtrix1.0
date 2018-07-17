#ifndef AwtrixWeatherHumApplication_h
#define AwtrixWeatherHumApplication_h

#include <IApplication.h>
#include <../Awtrix/config.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class WeatherHumApp : public IApplication
{
    private:
        uint16_t fire[8][32];
        float temperature;
        float humidity;
        String icon;
        String city;

    public:


        void render(DisplayManager&) override;
        void enable() override;
        String name = "WeatherHum";
};

#endif
