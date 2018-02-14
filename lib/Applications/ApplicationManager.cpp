#include <ApplicationManager.h>
#include <Arduino.h>

void ApplicationManager::loop() {
  unsigned long thisTick = millis();

  IApplication* application = activeApplication();
  if (application) {
    unsigned long delta = thisTick - lastTick;
    application->render();
  }

  lastTick = thisTick;
}

IApplication* ApplicationManager::activeApplication() {
  return NULL;
}