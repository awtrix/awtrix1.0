#ifndef AwtrixTimeApplication_h
#define AwtrixTimeApplication_h

#include <IApplication.h>
#include <../Awtrix/config.h>
#include <TimeLib.h>
#include <NTP.h>

class TimeApp : public IApplication
{
    private:
    bool blink=false;
    int loopCounter;
    NTP NTPclient;
    const char * monname[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    public:
        void render(DisplayManager&) override;
        void enable() override;
        String name = "Time";
};

#endif