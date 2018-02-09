#ifndef AwtrixMatrix_h
#define AwtrixMatrix_h

#include <Adafruit_NeoMatrix.h>

typedef struct { char red; char green; char blue; } AwtrixColor;
typedef struct { char x; char y; } AwtrixPosition;

class AwtrixMatrix
{
    public:
        static AwtrixMatrix& getInstance() {
            static AwtrixMatrix instance;
            return instance;
        }

        void clear();
        void setBrightness(int);
        void drawText(String, AwtrixPosition, AwtrixColor, boolean);

    private:
        // Singleton setup
        AwtrixMatrix();
        AwtrixMatrix(AwtrixMatrix const&);
        void operator = (AwtrixMatrix const&);

        Adafruit_NeoMatrix matrix;
        int brightness;

        void setup();
        uint32_t color(AwtrixColor);
};

#endif
