#ifndef AwtrixWeatherApplication_h
#define AwtrixWeatherApplication_h

#include <IApplication.h>
#include <WundergroundConditions.h>
#include <../Awtrix/config.h>


class WeatherApp : public IApplication
{
    private:
        WGConditions conditions;
        WundergroundConditions wunderground;
     
    public:
        WeatherApp() : wunderground(true) {}

        void render(DisplayManager&) override;
        void enable() override;
};

#endif
