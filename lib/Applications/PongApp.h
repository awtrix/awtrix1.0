#ifndef AwtrixPongApplication_h
#define AwtrixPongApplication_h

#include <IApplication.h>


class PongApp : public IApplication
{
    private:
        int paddleX = 1;
        int paddleY = 7;
        int oldPaddleX, oldPaddleY;
        int ballDirectionX = 1;
        int ballDirectionY = 1;
        int score = 0;
        int ballX, ballY, oldBallX, oldBallY;
        unsigned long prevMillis = 0;
    public:
        void render(DisplayManager&) override;
        void enable() override;
        void paddleLeft();
        void paddleRight();
};

#endif