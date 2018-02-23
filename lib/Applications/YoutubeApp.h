#ifndef AwtrixYoutubeApplication_h
#define AwtrixYoutubeApplication_h

#include <IApplication.h>
#include <WiFiClientSecure.h>

class YoutubeApp : public IApplication
{
    private:
        //const bool UpdateOnEnable = true;
        WiFiClientSecure client;
        String val;
        
    public:
        void render(DisplayManager&) override;
        void update() override;    
};

#endif
