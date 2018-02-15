#ifndef AwtrixWeatherApplication_h
#define AwtrixWeatherApplication_h

#include <IApplication.h>
#include <WundergroundConditions.h>

class WeatherApp : public IApplication
{
    private:
        WGConditions conditions;
        WundergroundConditions wunderground;

        unsigned long elapsed = 0;

    public:
        WeatherApp() : wunderground(true) {}

        void render(DisplayManager&) override;
        void tick(unsigned long) override;
        void enable() override;
};

#endif
