#ifndef AwtrixYoutubeApplication_h
#define AwtrixYoutubeApplication_h

#include <IApplication.h>
#include <ArduinoJson.h>
#include <../Awtrix/config.h>


class YoutubeApp : public IApplication
{
    private:
        const char *host = "www.googleapis.com";
        long subscribers = 0;

    public:
        void render(DisplayManager&) override;
        void enable() override; 
        String name = "Youtube";
    
};

#endif
