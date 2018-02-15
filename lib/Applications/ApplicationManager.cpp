#include <ApplicationManager.h>
#include <Arduino.h>

void ApplicationManager::loop() {
    unsigned long thisTick = millis();
    unsigned long delta = thisTick - lastTick;

    switchApplications();

    for (int i = 0; i < numberOfApplications; i++) {
        applications[i]->tick(delta);
    }

    IApplication* application = activeApplication();
    if (application) {
        application->render();
    }

    lastTick = thisTick;
}

void ApplicationManager::switchApplications() {

}

IApplication* ApplicationManager::activeApplication() {
    // Always return the last one for now
    return applications[numberOfApplications - 1];
}

void ApplicationManager::addApplication() {
    size_t size = numberOfApplications + 1;

    IApplication** newList = new IApplication*[size];
    memcpy(newList, applications, numberOfApplications * sizeof(IApplication*));

    numberOfApplications++;
    delete[] applications;
    applications = newList;
}
