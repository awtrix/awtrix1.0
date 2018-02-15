#include <Time.h>

const unsigned long UpdateThreshold = 3000l;

void Time::render(DisplayManager& display) {
    String time = timeClient.getFormattedTime();
    display.drawText(time, {1, 0}, {255, 255, 255});
}

void Time::tick(unsigned long delta) {
    elapsed += delta;

    if (elapsed >= UpdateThreshold) {
        timeClient.updateTime();
        elapsed = 0;
    }
}
