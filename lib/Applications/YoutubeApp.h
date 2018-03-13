#ifndef AwtrixYoutubeApplication_h
#define AwtrixYoutubeApplication_h

#include <IApplication.h>
#include <WiFiClientSecure.h>

class YoutubeApp : public IApplication
{
    private:

        String channelId = "YourChannelID";
        const bool UpdateOnEnable = true;
        WiFiClientSecure client;
        String val;
        
        const unsigned long UpdateThreshold = 1500000l;
    public:
        void render(DisplayManager&) override;
        void update() override;    
};

#endif
