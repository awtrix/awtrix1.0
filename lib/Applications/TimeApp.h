#ifndef AwtrixTimeApplication_h
#define AwtrixTimeApplication_h

#include <IApplication.h>
#include <TimeClient.h>

#define UTC_OFFSET 1

class TimeApp : public IApplication
{
    private:
        TimeClient timeClient;

        unsigned long elapsed = 0;

    public:
        TimeApp() : timeClient(UTC_OFFSET) {}

        void render(DisplayManager&) override;
        void tick(unsigned long) override;
        void enable() override;
};

#endif
