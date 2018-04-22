#include <PongApp.h>
#include "config.h"


boolean inPaddle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight) {
  boolean result = false;
  if ((x >= rectX && x <= (rectX + rectWidth)) &&
      (y >= rectY && y <= (rectY + rectHeight))) {
    result = true;
  }
  return result;
}


void PongApp::render(DisplayManager& display) {
    unsigned long currentMillis = millis();

    paddleX = map(paddle, 0, 1000, 0, 29);

    if (oldPaddleX != paddleX || oldPaddleY != paddleY) {
        display.fillRect(oldPaddleX, oldPaddleY, 4, 1,{0,0,0});
    }

    display.fillRect(paddleX, paddleY, 4, 1,{0,0,255});

    oldPaddleX = paddleX;
    oldPaddleY = paddleY;


    if (currentMillis - prevMillis >= 150) {
        prevMillis = currentMillis;

    if (ballX > 32 - 1 || ballX < 0) {
        ballDirectionX = -ballDirectionX;
    }

    if (ballY > 8 || ballY < 0) {
        ballDirectionY = -ballDirectionY;
    }

    if (inPaddle(ballX, ballY, paddleX, paddleY, 4, 1)) {
        if(ballX == paddleX && ballY == paddleY){
        ballDirectionX = -ballDirectionX;
        ballDirectionY = -ballDirectionY;
        }
        else if(ballX == paddleX + 3 && ballY == paddleY){
        ballDirectionX = ballDirectionX;
        ballDirectionY = -ballDirectionY;
        }
        else if(ballX == paddleX + 1 && ballY == paddleY){
        ballDirectionX = -ballDirectionX;
        ballDirectionY = -ballDirectionY;
        }
        else if(ballX == paddleX + 2 && ballY == paddleY){
        ballDirectionX = ballDirectionX;
        ballDirectionY = -ballDirectionY;
        }
    }


    ballX += ballDirectionX;
    ballY += ballDirectionY;

    if (oldBallX != ballX || oldBallY != ballY) {
        display.drawPixel(oldBallX, oldBallY,{0,0,0});
    }

    display.drawPixel(ballX, ballY,{150,150,0});

    oldBallX = ballX;
    oldBallY = ballY;

    }
    display.show();
    if(ballY > 8){
      
        display.drawText("PONG", {2, 0}, true,false,true);
        display.show();
        delay(1000);
        ballX = random(3,19);
        ballY = random(1,1);
        display.fillScreen(0);
        display.show();
        delay(200);
    }
 
}

void PongApp::enable() {
    Serial.println("PongApp started");
}


