#ifndef AwtrixYoutubeApplication_h
#define AwtrixYoutubeApplication_h

#include <IApplication.h>
#include <ArduinoJson.h>


class YoutubeApp : public IApplication
{
    private:
        const char *host = "www.googleapis.com";
        String apiKey = "AIzaSyBsNaNIocLRYh_kvBXkTzv9EPkSZFpS16M";            // YouTube Data API v3 key generated here: https://console.developers.google.com
        String channelId = "UCpGLALzRO0uaasWTsm9M99w";
        long subscribers,subscribersBefore = 0;
        String val;
        void getSubscribers(); 
    public:
        void render(DisplayManager&) override;
        void enable() override; 
          
};

#endif
