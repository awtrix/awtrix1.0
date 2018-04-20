#ifndef AwtrixTwitterApplication_h
#define AwtrixTwitterApplication_h

#include <IApplication.h>
#include <ArduinoJson.h>
#include <../Awtrix/config.h>
#include <ESP8266HTTPClient.h>

class TwitterApp : public IApplication
{
    private:
        int followers;
    public:
        void render(DisplayManager&) override;
        void enable() override; 
        String name = "Twitter";
};

#endif
