#include <DHT22App.h>

const unsigned long UpdateThreshold = 100000l;
float humidity;
float temperature;

static unsigned char temp[]={0x1c22221414141408};
static unsigned char hum[]={0x63,0x55,0x36,0x8,0x36,0x55,0x63,0x0};


void DHT22App::render(DisplayManager& display) {
    display.drawBitmap(temp, {0, 0}, {255, 0, 0}, 8, 8);
    display.drawText(String(temperature) + "\xA7", {12, 0}, {0xeb, 0xb7, 0x3d}, false);
}

void DHT22App::enable() {
    dht.setup(SENSOR_PIN);
    humidity= dht.getHumidity();
    temperature= dht.getTemperature();
}

void DHT22App::tick(unsigned long delta) {
    elapsed += delta;

    if (elapsed >= UpdateThreshold) {
        humidity= dht.getHumidity();
        temperature= dht.getTemperature();
        elapsed = 0;
    }
}
