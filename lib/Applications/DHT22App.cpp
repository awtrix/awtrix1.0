#include <DHT22App.h>

const unsigned long UpdateThreshold = 100000l;
float humidity;
float temperature;
DHT dht(DHTPIN, DHTTYPE);
static unsigned char temp[]={0x10,0x28,0x28,0x28,0x28,0x44,0x44,0x38};
static unsigned char tempInner[]={0x00,0x10,0x10,0x10,0x10,0x38,0x38,0x00};

void DHT22App::render(DisplayManager& display) {
    display.drawBitmap(temp, {0, 0}, {255, 0, 0}, 8, 8);
    display.drawBitmap(tempInner, {0, 0}, {0, 50, 255}, 8, 8);
    display.drawText(String(temperature), {9, 0}, {200, 50, 0}, false,false);

}

void DHT22App::enable() {
    dht.begin();
    humidity= dht.readHumidity();
    temperature= dht.readTemperature();
}

void DHT22App::tick(unsigned long delta) {
    elapsed += delta;

    if (elapsed >= UpdateThreshold) {
        humidity= dht.readHumidity();
        temperature= dht.readTemperature();
        elapsed = 0;
    }
}
