#include <DHT22App.h>

const unsigned long UpdateThreshold = 100000l;
float humidity;
float temperature;

static unsigned char rain[]={0x80,0x10,0x40,0x0,0x90,0x0,0x28,0x80};
static unsigned char snow[]={0x63,0x55,0x36,0x8,0x36,0x55,0x63,0x0};


void DHT22App::render(DisplayManager& display) {
    display.drawText(String(temperature) + "\xA7", {12, 0}, {0xeb, 0xb7, 0x3d}, false);
}

void DHT22App::enable() {
   dht.setup(SENSOR_PIN);
}

void DHT22App::tick(unsigned long delta) {
    elapsed += delta;

    if (elapsed >= UpdateThreshold) {
        humidity= dht.getHumidity();
        temperature= dht.getTemperature();
        elapsed = 0;
    }
}
