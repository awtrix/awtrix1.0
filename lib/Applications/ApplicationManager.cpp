#include <ApplicationManager.h>
#include <Arduino.h>

#include <TimeApp.h>
#include <WeatherApp.h>
#include <YoutubeApp.h>
#include <DHT22App.h>
#include <PetApp.h>
#include <GolApp.h>
#include <PlasmaApp.h>

IApplication* ApplicationManager::getApplicationWithName(String name) {
    if (name == "Time") {
        return new TimeApp();
    }

    if (name == "Weather") {
        return new WeatherApp();
    }

    if (name == "DHT22") {
        return new DHT22App();
    }

    if (name == "Youtube") {
        return new YoutubeApp();
    }

     if (name == "Pet") {
        return new PetApp();
    }

    if (name == "Gol") {
        return new GolApp();
    }

    if (name == "Plasma") {
        return new PlasmaApp();
    }
    return NULL;
}

void ApplicationManager::loop() {
    unsigned long thisTick = millis();
    unsigned long delta = thisTick - lastTick;

    applicationRuntime += delta;
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
    if (activeApplicationIndex < 0 && numberOfApplications > 0) {
        // TODO: Check for nullptr
        applications[0]->enable();
        activeApplicationIndex = 0;
        return;
    }

    if (applicationRuntime >= activeApplication()->DefaultDisplayTime) {
        int newIndex = activeApplicationIndex + 1;
        if (newIndex >= numberOfApplications) {
            newIndex = 0;
        }

        if (newIndex != activeApplicationIndex) {
            applications[activeApplicationIndex]->disable();
            applications[newIndex]->enable();

            activeApplicationIndex = newIndex;
            DisplayManager::getInstance().wipe({500});
            DisplayManager::getInstance().clear();
        }

        applicationRuntime = 0;
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
