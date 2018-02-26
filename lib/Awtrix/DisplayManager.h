#ifndef AwtrixDisplayManager_h
#define AwtrixDisplayManager_h

#include <Adafruit_NeoMatrix.h>

typedef struct { char red; char green; char blue; } AwtrixColor;
typedef struct { char red; char green; char blue; } AwtrixColorHSV;
typedef struct { char x; char y; } AwtrixPosition;

enum command_t { 
    settings_get, settings_set, settings_reset, brightness, text, color, screen
};

class DisplayManager
{
    private:
        // Singleton setup
        DisplayManager();
        DisplayManager(DisplayManager const&);
        void operator = (DisplayManager const&);

        Adafruit_NeoMatrix matrix;
        int brightness;
        int fontsize;
        void setup();
        uint32_t color(AwtrixColor);
        uint32_t colorHSV(AwtrixColorHSV);
        uint32_t Wheel(byte,int);
    public:
        static DisplayManager& getInstance() {
            static DisplayManager instance;
            return instance;
        }

        bool executeCommand(command_t, String);
        void drawApp(const uint16_t[], String,AwtrixPosition, AwtrixColor, bool, bool, int, int);
        void clear();
        void refresh();
        void wipe(int);
        void show();
        void setBrightness(int);
        void scrollText(String,AwtrixColor);
        void drawText(String, AwtrixPosition, AwtrixColor, boolean,boolean);
        void drawBitmap(unsigned char[], AwtrixPosition, AwtrixColor, int16_t, int16_t);
        void colorWipe(AwtrixColor);
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
};

#endif
