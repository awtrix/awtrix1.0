#ifndef AwtrixWeatherApplication_h
#define AwtrixWeatherApplication_h

#include <IApplication.h>
#include <WundergroundConditions.h>
#include <Settings.h>

class WeatherApp : public IApplication
{
    private:

        String WUNDERGROUND_API_KEY=      "b9cd2ae34c2974b6";
        String WUNDERGROUND_LANGUAGE=     "DE";
        String WUNDERGROUND_ZMW_CODE=     "00000.8.10641";
        AwtrixSettings& settings = AwtrixSettings::getInstance();
        WGConditions conditions;
        WundergroundConditions wunderground;
        
        const unsigned long UpdateThreshold = 150000l;

    public:
        WeatherApp() : wunderground(true) {}

        void render(DisplayManager&) override;
        void update() override;
};

#endif
