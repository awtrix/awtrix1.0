#ifndef AwtrixYoutubeApplication_h
#define AwtrixYoutubeApplication_h

#include <IApplication.h>

class YoutubeApp : public IApplication
{
    private:
        
        unsigned long elapsed = 0;
    public:
        void render(DisplayManager&) override;
        void tick(unsigned long) override;
        void enable() override;    
};

#endif
