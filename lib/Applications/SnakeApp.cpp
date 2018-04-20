#include <SnakeApp.h>
#include "config.h"
// direction
const int TOP    = 0;
const int RIGHT  = 1;
const int BOTTOM = 2;
const int LEFT   = 3;

// Snake
const int MAX_SNAKE_LENGTH = 15;

// Variables

                            // direction of movement
int snakeX[MAX_SNAKE_LENGTH];                      // X-coordinates of snake
int snakeY[MAX_SNAKE_LENGTH];                      // Y-coordinates of snake
int snakeLength = 1;                               // nr of parts of snake
unsigned long prevTime = 0;                        // for gamedelay (ms)
unsigned long delayTime = 200;                     // Game step in ms

int fruitX, fruitY;
unsigned long fruitPrevTime = 0;
unsigned long fruitBlinkTime = 1000/250;

int matrixColor;
  

void userLose(){

  
  snakeLength = 1;

}

void userWin(){
 

  
  snakeLength = 1;

}


boolean inPlayField(int x, int y){
  return (x>=0) && (x<32) && (y>=0) && (y<8);
}

boolean isPartOfSnake(int x, int y){
  for(int i=0; i<snakeLength-1; i++)
  {
    if((x == snakeX[i]) && (y == snakeY[i]))
      return true;
  }
  return false;
}


void snakeCheck(){  
    for(int i=1; i<snakeLength; i++)
    {
      // snake touches itself
      if((snakeX[0] == snakeX[i]) && (snakeY[0] == snakeY[i])) 
        userLose();
    }
    if (snakeLength == MAX_SNAKE_LENGTH)
      userWin();
}

void makeFruit(){
  int x, y;
  x = random(0, 32);
  y = random(0, 8);
  while(isPartOfSnake(x, y)){
    x = random(0, 32);
    y = random(0, 8);
  }
  fruitX = x;
  fruitY = y;
}



void nextstep(){  
  for(int i = snakeLength; i > 0; i--)
  {
    if((direction == RIGHT) && (snakeX[0]-snakeLength == 31))
      snakeX[0] = -1;
    else if((direction == LEFT) && (snakeX[0]+ snakeLength == 0))
      snakeX[0] = 32;
    else 
      snakeX[i] = snakeX[i-1];
    
    if((direction == TOP) && (snakeY[0]+snakeLength == 0))
      snakeY[0] = 8;
    else if((direction == BOTTOM) && (snakeY[0]-snakeLength == 7))
      snakeY[0] = -1;
    else 
      snakeY[i] = snakeY[i-1];      
  }
  
  switch(direction)
  {
    case TOP:
      snakeY[0] = snakeY[0]-1;
      break;
    case RIGHT:
      snakeX[0] = snakeX[0]+1;
      break;
    case BOTTOM:
      snakeY[0] = snakeY[0]+1;
      break;
    case LEFT:
      snakeX[0]=snakeX[0]-1;
      break;
  }
  
  if((snakeX[0] == fruitX) && (snakeY[0] == fruitY))
  {
    snakeLength++;
    if(snakeLength < MAX_SNAKE_LENGTH)
      makeFruit();
    else 
      fruitX = fruitY = -1;
   
  }
  snakeCheck();  
}

void SnakeApp::enable() {
     Serial.println("SnakeApp started");
    randomSeed(analogRead(0));
    snakeX[0] = 4;
    snakeY[0] = 7;
    for(int i=1; i<MAX_SNAKE_LENGTH; i++)
    snakeX[i] = snakeY[i] = -1; 
    makeFruit();
}

void SnakeApp::render(DisplayManager& display) {  
    unsigned long currentTime = millis();
    if(currentTime - prevTime >= delayTime)
    {
      nextstep(); 
      prevTime = currentTime;
    }
    
    display.clear();
    for(int i=0; i<snakeLength; i++)
        display.drawPixel(snakeX[i], snakeY[i], {0,255,0});


    if(inPlayField(fruitX, fruitY)){
        unsigned long currenttime = millis();
        if(currenttime - fruitPrevTime >= fruitBlinkTime)
        {
        //fruitLed = (fruitLed == LED_RED) ? LED_OFF : LED_RED;
        fruitPrevTime = currenttime;
        }
        display.drawPixel(fruitX, fruitY, {255,0,0});
  }



        display.show();      
}








