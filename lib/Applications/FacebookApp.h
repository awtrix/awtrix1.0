#ifndef AwtrixFacebookApplication_h
#define AwtrixFacebookApplication_h

#include <IApplication.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <../Awtrix/config.h>


class FacebookApp : public IApplication
{
    private:
        
        int pageLikes;
        const char* host = "graph.facebook.com"; 
      
    public:
        
        void render(DisplayManager&) override; 
        void enable() override; 
};

#endif
