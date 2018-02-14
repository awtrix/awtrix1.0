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

void ApplicationManager::addApplication() {
    size_t size = numberOfApplications + 1;

    IApplication** newList = new IApplication*[size];
    memcpy(newList, applications, numberOfApplications * sizeof(IApplication*));

    numberOfApplications++;
    delete[] applications;
    applications = newList;
}
