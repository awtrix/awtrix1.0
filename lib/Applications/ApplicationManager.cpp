#include <ApplicationManager.h>
#include <Arduino.h>

#include <TimeApp.h>
#include <WeatherApp.h>
#include <YoutubeApp.h>

IApplication* ApplicationManager::getApplicationWithName(String name) {
    if (name == "Time") {
        return new TimeApp();
    }

    if (name == "Weather") {
        return NULL;
    }

    if (name == "Youtube") {
        return NULL;
    }

    return NULL;
} 

void ApplicationManager::loop() {
    unsigned long thisTick = millis();
    unsigned long delta = thisTick - lastTick;

    switchApplications();

    for (int i = 0; i < numberOfApplications; i++) {
        applications[i]->tick(delta);
    }

    IApplication* application = activeApplication();
    if (application) {
        application->render(DisplayManager::getInstance());
    }

    lastTick = thisTick;
}

void ApplicationManager::switchApplications() {
    // Always set the last application to active
    int oldIndex = activeApplicationIndex;
    int newIndex = numberOfApplications - 1;

    if (oldIndex != newIndex) {
        if (applications[oldIndex]) {
            applications[oldIndex]->disable();
        }

        applications[newIndex]->enable();
        activeApplicationIndex = newIndex;
    }
}

IApplication* ApplicationManager::activeApplication() {
    return applications[activeApplicationIndex];
}

bool ApplicationManager::addApplication(String name) {
    IApplication* applicationToAdd = getApplicationWithName(name);
    if (!applicationToAdd) {
        return false;
    }

    size_t size = numberOfApplications + 1;

    IApplication** newList = new IApplication*[size];
    memcpy(newList, applications, numberOfApplications * sizeof(IApplication*));

    numberOfApplications++;
    delete[] applications;
    applications = newList;

    applications[numberOfApplications - 1] = applicationToAdd;

    return true;
}
