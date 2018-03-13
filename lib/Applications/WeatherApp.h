#ifndef AwtrixWeatherApplication_h
#define AwtrixWeatherApplication_h

#include <IApplication.h>
#include <WundergroundConditions.h>
#include <Settings.h>

class WeatherApp : public IApplication
{
    private:

        String WUNDERGROUND_API_KEY=      "YourAPIKey";
        String WUNDERGROUND_LANGUAGE=     "DE";
        String WUNDERGROUND_ZMW_CODE=     "YourZMWCode";
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
