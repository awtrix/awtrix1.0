#ifndef AwtrixTimeApplication_h
#define AwtrixTimeApplication_h

#include <IApplication.h>
#include <TimeClient.h>

#define UTC_OFFSET 1

class TimeApp : public IApplication
{
    private:
        TimeClient timeClient;
        const unsigned long UpdateThreshold = 30000l;

    public:
        TimeApp() : timeClient(UTC_OFFSET) {}

        void render(DisplayManager&) override;
        void update() override;
};

#endif
