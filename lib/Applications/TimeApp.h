#ifndef AwtrixTimeApplication_h
#define AwtrixTimeApplication_h

#include <IApplication.h>
#include <../Awtrix/config.h>
#include <NtpClientLib.h>


class TimeApp : public IApplication
{
    private:
    String time1;
    bool blink=false;
    public:
        

       

        void render(DisplayManager&) override;
        void enable() override;
};

#endif
