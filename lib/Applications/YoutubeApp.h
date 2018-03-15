#ifndef AwtrixYoutubeApplication_h
#define AwtrixYoutubeApplication_h

#include <IApplication.h>
#include <AwtrixWiFi.h>

class YoutubeApp : public IApplication
{
    private:

        String channelId = "UCpGLALzRO0uaasWTsm9M99w";
        const bool UpdateOnEnable = true;
        WiFiClientSecure client1;
        String val;
        const unsigned long UpdateThreshold = 35000l;
    public:
        void render(DisplayManager&) override;
        void update() override;    
};

#endif
