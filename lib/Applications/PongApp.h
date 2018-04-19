#ifndef AwtrixPongApplication_h
#define AwtrixPongApplication_h

#include <IApplication.h>


class PongApp : public IApplication
{
    private:
        void moveBall();
    public:
        void render(DisplayManager&) override;
        void enable() override;
        void paddleLeft();
        void paddleRight();
};

#endif