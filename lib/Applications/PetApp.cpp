#include <PetApp.h>
uint8_t
blinkIndex[] = { 1, 2, 3, 4, 3, 2, 1 },
blinkCountdown = 30, // Countdown to next blink (in frames)
gazeCountdown  =  200, // Countdown to next eye movement
gazeFrames     =  200; // Duration of eye movement (smaller = faster)
int8_t
eyeX = 9, eyeY = 3,   // Current eye position
newX = 9, newY = 3,   // Next eye position
dX   = 6, dY   = 0;   // Distance from prior to new position

static unsigned char  
sadBlinkImg[][8]  = {    // Eye animation frames
  {0x24, 0x42, 0x81, 0x3c, 0x7e, 0xff, 0xff, 0xff},
  {0x24, 0x42, 0x81, 0x00, 0x7e, 0xff, 0xff, 0xff},
  {0x24, 0x42, 0x81, 0x00, 0x00, 0x7e, 0xff, 0xff},
  {0x24, 0x42, 0x81, 0x00, 0x00, 0x00, 0x7e, 0xff},
  {0x24, 0x42, 0x81, 0x00, 0x00, 0x00, 0x00, 0xff} 
};
 
static unsigned char  
blinkImg[][8]  = {
  {0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c},
  {0x00, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c},
  {0x00, 0x00, 0x3c, 0xff, 0xff, 0xff, 0x3c, 0x00},
  {0x00, 0x00, 0x00, 0x3c, 0xff, 0x7e, 0x18, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x81, 0x7e, 0x00, 0x00} 
};
 
static unsigned char  
happyBlinkImg[][8]  = {
  {0x3c, 0x7e, 0xff, 0xff, 0xff, 0x00, 0x81, 0x7e},
  {0x00, 0x7e, 0xff, 0xff, 0xff, 0x00, 0x81, 0x7e},
  {0x00, 0x00, 0x7e, 0xff, 0xff, 0x00, 0x81, 0x7e},
  {0x00, 0x00, 0x00, 0x7e, 0xff, 0x00, 0x81, 0x7e},
  {0x00, 0x00, 0x00, 0x7e, 0x81, 0x00, 0x81, 0x7e} 
};
 
static unsigned char  
annoyedBlinkImg[][8]  = {
  {0x81, 0x66, 0x00, 0xff, 0xff, 0xff, 0x7e, 0x3c},
  {0x81, 0x66, 0x00, 0xff, 0xff, 0xff, 0x7e, 0x00},
  {0x81, 0x66, 0x00, 0xff, 0xff, 0x7e, 0x00, 0x00},
  {0x81, 0x66, 0x00, 0xff, 0x7e, 0x00, 0x00, 0x00},
  {0x81, 0x66, 0x00, 0x81, 0x7e, 0x00, 0x00, 0x00} 
};

void PetApp::render(DisplayManager& display) {
   if (PET_MOOD == 0){
  display.drawBitmap(sadBlinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{6, 0},eyeColor, 8, 8 );
  display.drawBitmap(sadBlinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{18, 0}, eyeColor, 8, 8);
    }

if (PET_MOOD == 1){
  display.drawBitmap(blinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{6, 0},eyeColor, 8, 8 );
  display.drawBitmap(blinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{18, 0},eyeColor, 8, 8 );
    }

if (PET_MOOD == 2){
  display.drawBitmap(happyBlinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{6, 0}, eyeColor, 8, 8);
  display.drawBitmap(happyBlinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{18, 0}, eyeColor, 8, 8);
    }

if (PET_MOOD == 3){
  display.drawBitmap(annoyedBlinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{6, 0},eyeColor, 8, 8);
  display.drawBitmap(annoyedBlinkImg[(blinkCountdown < sizeof(blinkIndex)) ? blinkIndex[blinkCountdown] : 0],{18, 0},eyeColor, 8, 8);
    }
 
    // Decrement blink counter.  At end, set random time for next blink.
    if(--blinkCountdown == 0) blinkCountdown = random(5, 180);
 
    // Add a pupil (2x2 black square) atop the blinky eyeball bitmap.
    // Periodically, the pupil moves to a new position...
    if(--gazeCountdown <= gazeFrames) {
      // Eyes are in motion - draw pupil at interim position
      display.drawRect(
      newX - (dX * gazeCountdown / gazeFrames)+6,
      newY - (dY * gazeCountdown / gazeFrames),
      2, 2, {0,0,0});

       display.drawRect(
      newX - (dX * gazeCountdown / gazeFrames)+18,
      newY - (dY * gazeCountdown / gazeFrames),
      2, 2, {0,0,0});
      if(gazeCountdown == 0) {    // Last frame?
        eyeX = newX; 
        eyeY = newY; // Yes.  What's new is old, then...
        do { // Pick random positions until one is within the eye circle
          if (PET_MOOD == 0){
          newX = random(0,7); 
          newY = random(5,7);
          dX   = newX-3;  
          dY   = newY-3;
          }

          if (PET_MOOD == 1){
          newX = random(7); 
          newY = random(7);
          dX   = newX - 3;  
          dY   = newY - 3;
          }

           if (PET_MOOD == 2){
          newX = random(7); 
          newY = random(4);
          dX   = newX - 3;  
          dY   = newY - 3;
          }

           if (PET_MOOD == 3){
          newX = random(7); 
          newY = random(3,7);
          dX   = newX - 3;  
          dY   = newY - 3;
          }
          
         
        } 
        while((dX * dX + dY * dY) >= 10);      
        dX            = newX - eyeX;             // Horizontal distance to move
        dY            = newY - eyeY;             // Vertical distance to move
        gazeFrames    = random(3, 15);           // Duration of eye movement
        gazeCountdown = random(gazeFrames, 120); // Count to end of next movement
      }
    } 
    else {
      // Not in motion yet -- draw pupil at current static position
      display.drawRect(eyeX+6, eyeY, 2, 2,{0,0,0});
      display.drawRect(eyeX+18, eyeY, 2, 2, {0,0,0});
    }
 delay(50);
    display.show();
}
