#include <TimeApp.h>

const unsigned long UpdateThreshold = 30000l;

void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
    display.drawText(time, {2, 0}, {0x4c, 0xb2, 0xd4}, true);
}

void TimeApp::tick(unsigned long delta) {
    elapsed += delta;

    if (elapsed >= UpdateThreshold) {
        timeClient.updateTime();
        elapsed = 0;
    }
}

void TimeApp::enable() {
    timeClient.updateTime();
}
