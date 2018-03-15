#ifndef AwtrixWeatherApplication_h
#define AwtrixWeatherApplication_h

#include <IApplication.h>
#include <WundergroundConditions.h>


class WeatherApp : public IApplication
{
    private:

        //String WUNDERGROUND_API_KEY=      "YourAPIKey";
        //String WUNDERGROUND_LANGUAGE=     "DE";
        //String WUNDERGROUND_ZMW_CODE=     "YourZMWKey";
        String WUNDERGROUND_API_KEY=      "b9cd2ae34c2974b6";
        String WUNDERGROUND_LANGUAGE=     "DE";
        String WUNDERGROUND_ZMW_CODE=     "00000.8.10641";
        WGConditions conditions;
        WundergroundConditions wunderground;
        

    public:
        WeatherApp() : wunderground(true) {}

        void render(DisplayManager&) override;
        void enable() override;
};

#endif
