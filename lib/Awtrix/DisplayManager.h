#ifndef AwtrixDisplayManager_h
#define AwtrixDisplayManager_h

#include <Adafruit_NeoMatrix.h>

typedef struct { char red; char green; char blue; } AwtrixColor;
typedef struct { char x; char y; } AwtrixPosition;


enum command_t { 
    settings_get, settings_set, settings_reset, brightness, text, color, screen
};

class DisplayManager
{
    public:
        static DisplayManager& getInstance() {
            static DisplayManager instance;
            return instance;
        }

        void clear();
        void setBrightness(int);
        void drawText(String, AwtrixPosition, AwtrixColor, boolean);
        void drawBitmap8x8(unsigned char[], AwtrixColor);
        bool executeCommand(command_t, String);


    private:
        // Singleton setup
        DisplayManager();
        DisplayManager(DisplayManager const&);
        void operator = (DisplayManager const&);

        Adafruit_NeoMatrix matrix;
        int brightness;

        void setup();
        uint32_t color(AwtrixColor);
};

#endif
