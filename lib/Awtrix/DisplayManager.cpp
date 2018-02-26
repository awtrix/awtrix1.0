#include <DisplayManager.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/TomThumb.h>
#include <Settings.h>

#define MATRIX_PIN          4
#define MATRIX_WIDTH        32
#define MATRIX_HEIGHT       8
#define SMALLFONT           0 //experimental
#define MATRIX_MODE         NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG
#define MATRIX_TYPE         NEO_GRB + NEO_KHZ800
#define BRIGHTNESS          150

DisplayManager::DisplayManager() : matrix(MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_PIN, MATRIX_MODE, MATRIX_TYPE) {
    setup();
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
    matrix.setTextColor(color({255, 255, 255}));
    matrix.setBrightness(BRIGHTNESS);
    clear();
}

uint32_t DisplayManager::Wheel(byte WheelPos, int pos) {
  if(WheelPos < 85) {
   return matrix.Color((WheelPos * 3)-pos, (255 - WheelPos * 3)-pos, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return matrix.Color((255 - WheelPos * 3)-pos, 0, (WheelPos * 3)-pos);
  } else {
   WheelPos -= 170;
   return matrix.Color(0, (WheelPos * 3)-pos, (255 - WheelPos * 3)-pos);
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

void DisplayManager::clear() {
    matrix.fillScreen(0);
    matrix.show();
}

void DisplayManager::refresh() {
   matrix.drawPixel(0, MATRIX_HEIGHT - 1, matrix.Color(0, 0, 255));
   matrix.show();
}

void DisplayManager::show() {
   matrix.show();
}

void DisplayManager::setBrightness(int value) {
    brightness = value;
    matrix.setBrightness(brightness);
    matrix.show();
}

void DisplayManager::drawText(String text, AwtrixPosition position, AwtrixColor textColor, boolean refresh,boolean small) {
    if (refresh) {
        matrix.clear();
    }
    if (small) {
        matrix.setFont(&TomThumb);
    }else{
        matrix.setFont();
    }

    matrix.setTextColor(color(textColor));
    matrix.setCursor(position.x, position.y);
    matrix.print(text);
    matrix.show();
    matrix.setFont();
}

void DisplayManager::drawApp(const uint16_t bmp[], String text, AwtrixPosition position, AwtrixColor textColor, bool scroll,bool autoScroll,int speed, int wait) {
    int pixelsInText = (text.length() * 7);
    int x = 32;
if (autoScroll) {
    if (text.length()>4){
        while(x > (32 - (pixelsInText+32))){
        matrix.clear();
        matrix.setCursor(--x, 0);
        matrix.print(text);
        matrix.setTextColor(color(textColor));
        matrix.drawRGBBitmap(0,0,bmp,8,8);
        matrix.drawFastVLine(8, 0, 8, 0);
        matrix.show();
        delay(speed);
        }
    }else{
        matrix.setTextColor(color(textColor));
        matrix.setCursor(position.x+9, position.y);
        matrix.print(text);
        matrix.drawRGBBitmap(0,0,bmp,8,8);
        matrix.show();
        matrix.setFont();
        }
    }
    delay(wait);
}


void DisplayManager::drawBitmap(unsigned char bmp[], AwtrixPosition position , AwtrixColor bmpColor, int16_t width, int16_t height) {
    matrix.drawBitmap(position.x, position.y, bmp, width, height, color(bmpColor));
}

void DisplayManager::flashProgress(unsigned int progress, unsigned int total) {
    unsigned long pixelColor = color({0, 255, 0});
    
    long num = MATRIX_WIDTH * MATRIX_HEIGHT * progress / total;
    for (unsigned char y = 0; y < MATRIX_HEIGHT; y++) {
        for (unsigned char x = 0; x < MATRIX_WIDTH; x++) {
            if (num-- > 0) matrix.drawPixel(x, MATRIX_HEIGHT - y - 1, Wheel((num*16) & 255,0));
        }
    }
    matrix.setCursor(1, 0);
    matrix.print(F("FLASH"));
    matrix.setTextColor(color({255, 255, 255}));
    matrix.show();
}


void DisplayManager::scrollText(String text, AwtrixColor textColor) {
    int x = 32;
    int pixelsInText = (text.length() * 7) + 32;
    matrix.setCursor(x, 0);
    matrix.print(text);
    matrix.show();
    
    while(x > (32 - pixelsInText)) {
        matrix.clear();
        matrix.setCursor(--x, 0);
        matrix.print(text);
        matrix.setTextColor(color(textColor));
        matrix.show();
        delay(20);
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

bool DisplayManager::executeCommand(command_t command, String payload)
{
    switch (command) {
        case command_t::settings_get:
            break;

        case command_t::settings_set:
            break;

        case command_t::settings_reset:
            break;

        case command_t::brightness:
            brightness = payload.toInt();
            break;

        case command_t::text:
            break;

        case command_t::color:
            break;

        case command_t::screen:
            break;
    }

    return true;
}

uint32_t DisplayManager::color(AwtrixColor color)
{
    return matrix.Color(color.red, color.green, color.blue);
    
}



void DisplayManager::rotate(int wait){


    
for(uint16_t i=0; i<32+1; i++) {
      matrix.drawFastVLine(i, 0, 8, Wheel((i*8) & 255,0));
     matrix.drawFastVLine(i-1, 0, 8, 0);

      matrix.show();
      delay(20);
  }
  }




/*
void checkLight() {
    int reading = analogRead(A0);
    int brightness = map(reading, 0, 1024, 10, 200);
    matrix.setBrightness(brightness);
}




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
