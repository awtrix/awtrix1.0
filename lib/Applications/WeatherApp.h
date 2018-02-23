#ifndef AwtrixWeatherApplication_h
#define AwtrixWeatherApplication_h

#include <IApplication.h>
#include <WundergroundConditions.h>

class WeatherApp : public IApplication
{
    private:
        WGConditions conditions;
        WundergroundConditions wunderground;
        
        const unsigned long UpdateThreshold = 150000l;

    public:
        WeatherApp() : wunderground(true) {}

        void render(DisplayManager&) override;
        void update() override;
};

#endif