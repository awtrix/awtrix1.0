#ifndef AwtrixFacebookApplication_h
#define AwtrixFacebookApplication_h

#include <IApplication.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> 


class FacebookApp : public IApplication
{
    private:
        WiFiClientSecure client;
        int pageLikes;
        DynamicJsonBuffer jsonBuffer;

        const char* host = "graph.facebook.com"; 

        //This can be done at developers.facebook.com. After the APP is created, note the App ID and App Secret.
        //Wanna test the access for your APP? Head over to https://developers.facebook.com/tools/explorer/
        //Enter the following: AAA?access_token=BBB|CCC&fields=fan_count
            //AAA = Facebook Page ID or name,
            //BBB = App ID
            //CCC = App Secret      
        
        const String url = "/205403270192886?access_token=413044212451682|1b83bfa010904e1a18267c5845f59efe&fields=fan_count"; //AAA?access_token=BBB|CCC&fields=fan_count

        const int httpsPort = 443; 
        const char* fingerprint = "bd258c1f62a4a6d9cf7d9812d22e2ff57e84fb36"; //https://github.com/gbrault/esp8266-Arduino/blob/master/doc/esp8266wifi/client-secure-examples.md#how-to-verify-servers-identity


        const bool UpdateOnEnable = true;               // If true, the update function will be called once everytime the app start
        
        const unsigned long UpdateThreshold = 30000l;   // Time until the update function is called. 
                                                        // (Optional, remove line to use global threshhold)
       
    public:
        
        void render(DisplayManager&) override; 
        void enable() override; 
        void update() override; 
};

#endif
