#include <PlasmaApp.h>
#define TODISPLAY(x) ((x) + 1) * 120
int t = 0;
int r, g, b;

void PlasmaApp::render(DisplayManager& display) {
  display.clear();
 
  for(int y = 0; y < 8; y++)
    for(int x = 0; x < 32; x++)
    {
      double cx = x / (double) 16 + 0.5 * sin(t / 10.);
      double cy = y / (double) 16 + 0.5 * cos(t / 6.);
      double v = sin(sqrt(100 * (cx*cx+cy*cy) + 1) + t / 2.);

      switch(t / 300)
      {
        case 0:
          r = 1;
          g = cos(v * PI);
          b = sin(v * PI);
          break;
          
        case 1:
          r = sin(v * PI);
          g = cos(v * PI);
          b = 0;
          break;
          
        case 2:
          r = sin(v * PI);
          g = sin(v * PI + 2 * PI / 3);
          b = sin(v * PI + 4 * PI / 3);
          break;
          
        case 4:
          t = 0;  // note no break

        case 3:
          r = g = b = sin(v * .75 * PI);
          break;
      }

      r = TODISPLAY(r);
      g = TODISPLAY(g);
      b = TODISPLAY(b);
      
      display.drawPixel(x ,y, {char(r), char(g), char(b)});
    }
    
  display.show();
  delay(20);

  t++;
}



void PlasmaApp::update() {
   
}
