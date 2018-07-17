#ifndef AwtrixDisplayManager_h
#define AwtrixDisplayManager_h

#include <Adafruit_NeoMatrix.h>
#include "config.h"

typedef struct { char red; char green; char blue; } AwtrixColor;
typedef struct { char x; char y; } AwtrixPosition;

enum command_t {
    settings_get, settings_set, settings_reset, bright, text, color, screen, notification
};

class DisplayManager
{
    private:
        // Singleton setup
        DisplayManager();
        DisplayManager(DisplayManager const&);
        void operator = (DisplayManager const&);
        int colorCircle;
        Adafruit_NeoMatrix matrix;
        AwtrixColor defaultTextColor;
        int fontsize;
        void setup();
        uint32_t color(AwtrixColor);
        uint32_t Wheel(byte);


    public:
        static DisplayManager& getInstance() {
            static DisplayManager instance;
            return instance;
        }

        bool executeCommand(command_t, String, String);
        void drawApp(const uint16_t[], String,AwtrixPosition, AwtrixColor, bool, int);
        void clear();
        void refresh();
        void wipe();

        void show();
        void setERR();
        void checkLight();
        void setBrightness(int);
        void setSleepBrightness(int);
        void setColor(AwtrixColor);
        void scrollText(String);
        void drawText(String, AwtrixPosition, boolean,boolean,boolean);
        void drawBitmap(unsigned char[], AwtrixPosition, AwtrixColor, int16_t, int16_t);
        void colorWipe(AwtrixColor);
        void fillScreen(int);
        void drawWeekday(int);
        void flashProgress(unsigned int, unsigned int);
        void drawRect(uint16_t ,uint16_t ,uint16_t ,uint16_t ,AwtrixColor);
        void drawPixel(uint16_t ,uint16_t ,AwtrixColor);
        void fillRect(uint16_t ,uint16_t ,uint16_t ,uint16_t ,AwtrixColor);
        void drawLine(uint16_t ,uint16_t ,uint16_t ,uint16_t ,AwtrixColor);
        void drawCircle(uint16_t ,uint16_t ,uint16_t ,AwtrixColor);
        void fillCircle(uint16_t ,uint16_t ,uint16_t ,AwtrixColor);
        void drawRoundRect(uint16_t ,uint16_t ,uint16_t,uint16_t,uint16_t ,AwtrixColor);
        void fillRoundRect(uint16_t ,uint16_t ,uint16_t,uint16_t,uint16_t ,AwtrixColor);
        void drawTriangle(uint16_t ,uint16_t ,uint16_t,uint16_t,uint16_t,uint16_t ,AwtrixColor);
        void fillTriangle(uint16_t ,uint16_t ,uint16_t,uint16_t,uint16_t,uint16_t ,AwtrixColor);
        void drawChar(uint16_t, uint16_t, char, AwtrixColor, uint16_t, uint8_t);
        void setLayout();
        void showBoot();
        void showSave();
};

#endif
