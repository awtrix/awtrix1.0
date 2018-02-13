#include <DisplayManager.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define MATRIX_PIN          4
#define MATRIX_WIDTH        32
#define MATRIX_HEIGHT       8
#define MATRIX_MODE         NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG
#define MATRIX_TYPE         NEO_GRB + NEO_KHZ800
#define BRIGHTNESS          150

DisplayManager::DisplayManager() : matrix(MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_PIN, MATRIX_MODE, MATRIX_TYPE) {
    setup();
}

void DisplayManager::setup() {
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setFont();
    matrix.setTextColor(color({255, 255, 255}));
    matrix.setBrightness(BRIGHTNESS);

    clear();
}

void DisplayManager::clear() {
    matrix.fillScreen(0);
    matrix.show();
}

void DisplayManager::setBrightness(int value) {
    brightness = value;
    matrix.setBrightness(brightness);
    matrix.show();
}

void DisplayManager::drawText(String text, AwtrixPosition position, AwtrixColor color, boolean refresh) {
    //matrix.setTextColor(matrix.Color(red, green, blue));
    if (refresh) {
        matrix.clear();
    }

    matrix.setCursor(position.x, position.y);
    matrix.print(text);
    matrix.show();
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

/*
#include <Ticker.h>
#include <Fonts/FreeMono9pt7b.h>

void matrixBitmap8x8(unsigned char bmp[],int red ,int green, int blue) {
    matrix.drawBitmap(0, 0, bmp, 8,8,matrix.Color(red, green, blue));
    matrix.drawLine(8, 0, 8, 8, matrix.Color(0, 0, 0));
}

void matrixScrollText() {
    matrix.show();
}

void matrixBoot(String IP) {
    for (int x = MATRIX_WIDTH; x > -60 - MATRIX_WIDTH; x--) {
        matrix.clear();
        matrix.setCursor(x, 0);
        matrix.print(IP);
        matrix.show();
        delay(40);
    }
}
    
void checkLight() {
    int reading = analogRead(A0);
    int brightness = map(reading, 0, 1024, 10, 200);
    matrix.setBrightness(brightness);
}

void matrixRefresh() {
   matrix.drawPixel(0, MATRIX_HEIGHT - 1, matrix.Color(0, 0, 255)); 
   matrix.show();
}

void matrixLoading(unsigned int progress, unsigned int total) {
    unsigned long color = matrix.Color(0, 255, 0);
    long num = MATRIX_WIDTH * MATRIX_HEIGHT * progress / total;
    for (unsigned char y = 0; y < MATRIX_HEIGHT; y++) {
        for (unsigned char x = 0; x < MATRIX_WIDTH; x++) {
            if (num-- > 0) matrix.drawPixel(x, MATRIX_HEIGHT-y-1, color);
        }
    }

    matrix.setCursor(1, 0);
    matrix.print(F("FLASH"));
    matrix.setTextColor(matrix.Color(255, 0, 0));
    matrix.show();
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

// -----------------------------------------------------------------------------
// Heartbeat
// -----------------------------------------------------------------------------

Ticker heartBeat;
bool beat = true;

void setupHeartbeat() {
    heartBeat.attach_ms(1000, heartBeatLoop);
}

void endHeartbeat() {
    heartBeat.detach();
}

void heartBeatLoop() {
    if (beat) {
        matrix.drawPixel(MATRIX_WIDTH-1,MATRIX_HEIGHT-1,matrix.Color(0, 255, 0));
    } else {
        matrix.drawPixel(MATRIX_WIDTH-1,MATRIX_HEIGHT-1,matrix.Color(0, 0, 0));
    }

    matrix.show();
    beat = !beat;
}
*/
