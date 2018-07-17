#include <DisplayManager.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/TomThumb.h>
#include <BMP.h>


#define MATRIX_PIN          4
#define MATRIX_WIDTH        32
#define MATRIX_HEIGHT       8
#define SMALLFONT           0 //experimental
#define MATRIX_MODE         NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG
#define MATRIX_TYPE         NEO_GRB + NEO_KHZ800

int period = 20;
unsigned long time_now = 0;

DisplayManager::DisplayManager() : matrix(MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_PIN, MATRIX_MODE, MATRIX_TYPE) {
    setup();
}

uint16_t Remap(uint16_t x, uint16_t y) {
  return MATRIX_WIDTH * y + x;
}

void DisplayManager::setup() {
    matrix.begin();
    
    matrix.setTextWrap(false);
    if (SMALLFONT){
        matrix.setFont(&TomThumb);
        fontsize= 5;
        }else{
        matrix.setFont();
        fontsize=0;
    };
    matrix.setTextColor(color({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B}));
    setBrightness(BRIGHTNESS);
    
    clear();
}

 void DisplayManager::setLayout(){
    matrix.setRemapFunction(Remap);
 }



uint32_t DisplayManager::Wheel(byte WheelPos) {

  
if (colorCircle==256) colorCircle=0;
Serial.println(WheelPos);
  if(WheelPos < 85) {
   return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



void DisplayManager::drawRect(uint16_t  x0, uint16_t  y0,uint16_t  x1,uint16_t  y1, AwtrixColor rectColor) {
    matrix.drawRect(x0, y0, x1, y1, color(rectColor));
    
}

void DisplayManager::fillRect(uint16_t  x0, uint16_t  y0,uint16_t  x1,uint16_t  y1, AwtrixColor rectColor) {
    matrix.fillRect(x0, y0, x1, y1, color(rectColor));
     
}

void DisplayManager::drawPixel(uint16_t  x, uint16_t  y, AwtrixColor pixelColor) {
    matrix.drawPixel(x, y, color(pixelColor));
   
}

void DisplayManager::drawLine(uint16_t  x0, uint16_t  y0,uint16_t  X1,uint16_t  Y1, AwtrixColor lineColor) {
    matrix.drawLine(x0, y0, X1, Y1, color(lineColor));
    
}

void DisplayManager::drawCircle(uint16_t  x0, uint16_t  y0, uint16_t  r, AwtrixColor circleColor) {
    matrix.drawCircle(x0, y0, r, color(circleColor));
    
}

void DisplayManager::fillCircle(uint16_t  x0, uint16_t  y0, uint16_t  r, AwtrixColor circleColor) {
    matrix.fillCircle(x0, y0, r, color(circleColor));
   
}

void DisplayManager::drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, AwtrixColor RoundRectColor) {
    matrix.drawRoundRect(x0, y0, w,h ,radius, color(RoundRectColor));
    
}

void DisplayManager::fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, AwtrixColor RoundRectColor) {
    matrix.fillRoundRect(x0, y0, w,h ,radius, color(RoundRectColor));
    
}

void DisplayManager::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, AwtrixColor triangleColor) {
    matrix.drawTriangle(x0, y0, x1, y1, x2, y2, color(triangleColor));
    
}

void DisplayManager::fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, AwtrixColor triangleColor) {
    matrix.fillTriangle(x0, y0, x1, y1, x2, y2, color(triangleColor));
    
}

void DisplayManager::drawChar(uint16_t x, uint16_t y, char c, AwtrixColor charColor, uint16_t bg, uint8_t size) {
    matrix.drawChar(x, y, c, color(charColor),bg, size);
    
}

void DisplayManager::fillScreen(int ScreenColor) {
    matrix.fillScreen(ScreenColor);
    
}

void DisplayManager::clear() {
    matrix.fillScreen(0); 
  
}

void DisplayManager::refresh() {
   matrix.drawPixel(0, 8 - 1, color({0, 0, 255}));
   matrix.show();
}

void DisplayManager::show() {
   matrix.show();
}


void DisplayManager::setBrightness(int value) {
    BRIGHTNESS=value;
    matrix.setBrightness(BRIGHTNESS);
}

void DisplayManager::setSleepBrightness(int value) {
    matrix.setBrightness(value);
}

void DisplayManager::setColor(AwtrixColor textColor) {
     matrix.setTextColor(color(textColor));

}

void DisplayManager::drawWeekday(int day) {

    for (int i=0; i <=6;i++){
        if (i==day){
            matrix.drawLine(2+i*4, 7, i*4+4, 7, color({200,200,200}));
        }else{
            matrix.drawLine(2+i*4, 7, i*4+4, 7, color({80,80,80}));
        }   
    }
    
}

void DisplayManager::setERR() {
    matrix.clear();
    matrix.setTextColor(color({255,0,0}));
    matrix.setFont();
    matrix.setBrightness(100);
    matrix.setCursor(0,0);
    matrix.print("CONF!");
    matrix.show();
}



void DisplayManager::drawText(String text, AwtrixPosition position, boolean refresh,boolean small,boolean gobalColor) {
    if (refresh) {
        matrix.clear();
    }
    if (small) {
        matrix.setFont(&TomThumb);
        matrix.setCursor(position.x+1, position.y+6);
    }else{
        matrix.setFont();
        matrix.setCursor(position.x, position.y);
    }
      if(RAINBOW & !SLEEP_MODE){
             if(millis() > time_now + period){
                time_now = millis();
                 matrix.setTextColor(Wheel(colorCircle));
                 ++colorCircle;
            }
            }else{
        matrix.setTextColor(color({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B}));
           
        }   
    matrix.print(text);

    matrix.setFont();
 
}


void DisplayManager::drawApp(const uint16_t bmp[], String text, AwtrixPosition position, AwtrixColor textColor, bool autoScroll, int wait) {
    int pixelsInText = (text.length() * 6);
    int x = 24;
    int s = map(SCROLL_SPEED,1,100,60,1);

if (autoScroll) {
    if (text.length()>4){
        while(x > (24 - (pixelsInText+24))){
        matrix.clear();
        matrix.setCursor(--x, 0);
            if(RAINBOW){
             if(millis() > time_now + period){
                time_now = millis();
                 matrix.setTextColor(Wheel(colorCircle));
                 ++colorCircle;
            }
            }else{
        matrix.setTextColor(color({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B}));
           
        }   
        matrix.print(text);

        matrix.drawRGBBitmap(0,0,bmp,8,8);
        matrix.drawFastVLine(8, 0, 8, 0);
        matrix.show();
     
        delay(s);
        }
    }else{
        matrix.setCursor(position.x+9, position.y);
            
       if(RAINBOW){
             if(millis() > time_now + period){
                time_now = millis();
                 matrix.setTextColor(Wheel(colorCircle));
                 ++colorCircle;
            }
            }else{
        matrix.setTextColor(color({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B}));
           
        }   
        matrix.print(text);
        
        matrix.drawRGBBitmap(0,0,bmp,8,8);
        matrix.show();
        matrix.setFont();
  
        }
    }
    if (text.length()>4) delay(wait);
    

}


void DisplayManager::drawBitmap(unsigned char bmp[], AwtrixPosition position , AwtrixColor bmpColor, int16_t width, int16_t height) {
    matrix.drawBitmap(position.x, position.y, bmp, width, height, color(bmpColor));
}


void DisplayManager::flashProgress(unsigned int progress, unsigned int total) {
    matrix.setBrightness(100);
    unsigned long pixelColor = color({0, 255, 0});
    
    long num = MATRIX_WIDTH * MATRIX_HEIGHT * progress / total;
    for (unsigned char y = 0; y < MATRIX_HEIGHT; y++) {
        for (unsigned char x = 0; x < MATRIX_WIDTH; x++) {
            if (num-- > 0) matrix.drawPixel(x, MATRIX_HEIGHT - y - 1, Wheel((num*16) & 255));
        }
    }
    matrix.setCursor(1, 0);
    matrix.print(F("FLASH"));
    matrix.setTextColor(color({255, 255, 255}));
    matrix.show();
}


void DisplayManager::scrollText(String text) {
    int x = 32;
    int s = map(SCROLL_SPEED,0,100,60,2);
    int pixelsInText = (text.length() * 7) + 32;
    matrix.setCursor(x, 0);
    matrix.print(text);
    matrix.show();
    
    while(x > (32 - pixelsInText)) {
        matrix.clear();
        matrix.setCursor(--x, 0);
        matrix.print(text);
        matrix.setTextColor(color({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B}));
        matrix.show();
        delay(s);
    }
}

void DisplayManager::colorWipe(AwtrixColor wipeColor) {
    for(uint16_t row=0; row < 8; row++) {
        for(uint16_t column=0; column < 32; column++) {
        matrix.drawPixel(column, row, color(wipeColor));
        matrix.show();
        }
    }
}


uint32_t DisplayManager::color(AwtrixColor color)
{
  return matrix.Color(color.red, color.green, color.blue);
    
}

void DisplayManager::wipe(){  
    matrix.clear();
    for(uint16_t i=0; i<32+1; i++) {
        matrix.drawFastVLine(i, 0, 8, Wheel((i*8) & 255));
        matrix.drawFastVLine(i-1, 0, 8, 0);
        matrix.show();
        delay(10);
    }
}



void DisplayManager::checkLight() {
    int brightnessAnalog = analogRead(A0);
    if (brightnessAnalog<300)
      {
        setBrightness(30);
      }else if(brightnessAnalog<400)
      {
         setBrightness(70);
      }else if(brightnessAnalog>500)
      {
         setBrightness(100);
      }else if(brightnessAnalog<600)
      {
         setBrightness(150);
      }else if(brightnessAnalog>600)
      {
         setBrightness(200);
      }
   
}




void DisplayManager::showBoot(){
    matrix.setFont(&TomThumb);
    matrix.setBrightness(BRIGHTNESS);
    matrix.setTextColor(color({255,0,00}));
    matrix.setCursor(4, 6);
    matrix.print("A");
    matrix.setTextColor(color({255,165,0}));
    matrix.setCursor(8, 6);
    matrix.print("W");
    matrix.setTextColor(color({255,255,0}));
    matrix.setCursor(12, 6);
    matrix.print("T");
    matrix.setTextColor(color({0,255,0}));
    matrix.setCursor(17, 6);
    matrix.print("R");
    matrix.setTextColor(color({51,51,204}));
    matrix.setCursor(21, 6);
    matrix.print("I");
    matrix.setTextColor(color({75,0,130}));
    matrix.setCursor(25, 6);
    matrix.print("X");
    matrix.show();
    matrix.setFont();
}

void DisplayManager::showSave(){
    matrix.clear();
    matrix.setBrightness(BRIGHTNESS);
    matrix.setTextColor(color({0,255,50}));
    matrix.setCursor(4, 0);
    matrix.print("SAVE");
    matrix.show();
}

/*


uint16_t *decodeColorData(unsigned char* data) {
    uint16_t *pixels = (uint16_t*) malloc(MATRIX_WIDTH * MATRIX_HEIGHT * 2);
    if (!pixels) {
        return NULL;
    }

    for (int i = 0; i < MATRIX_WIDTH * MATRIX_HEIGHT; i++) {
        pixels[i] = (data[2 * i] << 8) | (data[2 * i + 1]);
    }

    return pixels;
}
*/
