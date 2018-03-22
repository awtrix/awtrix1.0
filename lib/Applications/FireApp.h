#ifndef AwtrixFireApplication_h
#define AwtrixFireApplication_h

#include <IApplication.h>

#include <../Awtrix/config.h>
class FireApp : public IApplication
{
    private:
        uint16_t fire[8][32];

    public:


        void render(DisplayManager&) override;
        void enable() override;
};

#endif
