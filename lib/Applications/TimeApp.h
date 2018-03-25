#ifndef AwtrixTimeApplication_h
#define AwtrixTimeApplication_h

#include <IApplication.h>
#include <../Awtrix/TimeClient.h>
#include <../Awtrix/config.h>
class TimeApp : public IApplication
{
    private:
        TimeClient timeClient;
        bool blink=false;
    public:
        TimeApp() : timeClient(UTC_OFFSET) {}

        void render(DisplayManager&) override;
        void enable() override;
};

#endif
