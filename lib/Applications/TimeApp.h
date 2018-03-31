#ifndef AwtrixTimeApplication_h
#define AwtrixTimeApplication_h

#include <IApplication.h>
#include <../Awtrix/config.h>
#include <TimeLib.h>
#include <Time.h>
class TimeApp : public IApplication
{
    private:
    String time1;
    bool blink=false;
    int loopCounter;
    public:
        void render(DisplayManager&) override;
        void enable() override;
};

#endif
