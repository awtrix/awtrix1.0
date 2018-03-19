#ifndef AwtrixFacebookApplication_h
#define AwtrixFacebookApplication_h

#include <IApplication.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 
#include <..\Awtrix/config.h>


class FacebookApp : public IApplication
{
    private:
        
        int pageLikes;
        DynamicJsonBuffer jsonBuffer;

        const char* host = "graph.facebook.com"; 

        //This can be done at developers.facebook.com. After the APP is created, note the App ID and App Secret.
        //Wanna test the access for your APP? Head over to https://developers.facebook.com/tools/explorer/
        //Enter the following: AAA?access_token=BBB|CCC&fields=fan_count
            //AAA = Facebook Page ID or name,
            //BBB = App ID
            //CCC = App Secret      
        const int httpsPort = 443; 
       
    public:
        
        void render(DisplayManager&) override; 
        void enable() override; 
};

#endif
