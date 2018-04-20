#include <FireApp.h>
#include <../Awtrix/config.h>




void FireApp::render(DisplayManager& display) {
   static uint32_t ts = millis();

    if (millis() - ts > 100) {
        ts = millis();
		for (int x = 0; x < 32; x++) {
			fire[8 - 1][x] = rand() & 0x3FF;
		}
	}

	for (int y = 0; y < 8 - 1; y++) {
		for (int x = 0; x < 32; x++) {
			float v =
			    fire[(y + 1) % 8][(x - 1 + 32) % 32] +
			    fire[(y + 1) % 8][x] +
			    fire[(y + 1) % 8][(x + 1 + 32) % 32] +
			    fire[(y + 2) % 8][x];
			v /= 7.5;
			fire[y][x] = (int16_t)v;
		}
	}



	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 32; x++) {
			if (fire[y][x] < 256) {
				display.drawPixel(x, y, {fire[y][x], 0, 0});
			} else {
				display.drawPixel(x, y, {255, fire[y][x] - 256, 0});
			}
		}
	}

    display.show();
	delay(50);
}

void FireApp::enable() {
	        Serial.println("FireApp started");
    for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 32; x++) {
			fire[y][x] = 0;
		}
	}

	for (int x = 0; x < 32; x++) {
		fire[8 - 1][x] = rand() & 0x3FF;
	}
}

