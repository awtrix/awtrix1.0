#include <TimeApp.h>

void TimeApp::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
    display.drawText(time, {2, 0}, {255, 0, 0}, true,false);
}

void TimeApp::update() {
    timeClient.updateTime();
}
