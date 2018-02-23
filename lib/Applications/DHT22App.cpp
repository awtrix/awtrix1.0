#include <DHT22App.h>

#define DHTTYPE DHT22
#define DHTPIN 2

static unsigned char temp[]={0x10,0x28,0x28,0x28,0x28,0x44,0x44,0x38};
static unsigned char tempInner[]={0x00,0x10,0x10,0x10,0x10,0x38,0x38,0x00};

DHT22App::DHT22App() : dht(DHTPIN, DHTTYPE) {
    dht.begin();
}

void DHT22App::render(DisplayManager& display) {
    display.drawBitmap(temp, {0, 0}, {255, 0, 0}, 8, 8);
    display.drawBitmap(tempInner, {0, 0}, {0, 50, 255}, 8, 8);
    display.drawText(String(temperature), {9, 0}, {200, 50, 0}, false, false);
}

void DHT22App::update() {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
}
