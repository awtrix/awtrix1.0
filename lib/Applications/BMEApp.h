#ifndef AwtrixBMEApplication_h
#define AwtrixBMEApplication_h

#include <IApplication.h>
#include <Wire.h>
#include <BME280_t.h>


class BMEApp : public IApplication
{
    private:
       
        int humidity;
        int temperature;
        char bufout[10];
        BME280<> BMESensor;

    public:
        BMEApp();    
        void render(DisplayManager&) override;
        void enable() override;
        String name = "BME";
};  

#endif
