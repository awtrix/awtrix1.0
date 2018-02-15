#ifndef AwtrixTimeApplication_h
#define AwtrixTimeApplication_h

#include <IApplication.h>
#include <TimeClient.h>

#define UTC_OFFSET 1

class Time : public IApplication
{
    private:
        TimeClient timeClient;

        unsigned long elapsed = 0;

    public:
        Time() : timeClient(UTC_OFFSET) {}

        void render(DisplayManager&) override;
        void tick(unsigned long) override;
};

#endif
