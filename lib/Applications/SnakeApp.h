#ifndef AwtrixSnakeApplication_h
#define AwtrixSnakeApplication_h

#include <IApplication.h>
#include <DisplayManager.h>

class SnakeApp : public IApplication
{
    private:

    public:
        void render(DisplayManager&) override;
        void enable() override;
                String name = "Snake";
};

#endif