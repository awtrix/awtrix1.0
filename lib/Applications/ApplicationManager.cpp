#include <ApplicationManager.h>
#include <Arduino.h>
#include <TimeApp.h>
#include <WeatherApp.h>
#include <YoutubeApp.h>
#include <DHT22App.h>
#include <PetApp.h>
#include <GolApp.h>
#include <FacebookApp.h>
#include <FireApp.h>
#include <TwitterApp.h>
#include <../Awtrix/config.h>
#include <TimeLib.h>


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

        if (name == "Facebook") {
        return new FacebookApp();
    }

      if (name == "Fire") {
        return new FireApp();
    }

          if (name == "Twitter") {
        return new TwitterApp();
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



void ApplicationManager::nextApplication() {
    applicationRuntime=0;
        DisplayManager::getInstance().drawPixel(31,7,{255,100,0}); 
        DisplayManager::getInstance().show();
        applications[activeApplicationIndex]->disable();

        AppIndex = activeApplicationIndex + 1;
            if (AppIndex >= numberOfApplications) {
                AppIndex = 0;
            }
        applications[AppIndex]->enable();
        DisplayManager::getInstance().wipe({500});
        activeApplicationIndex = AppIndex;
}

void ApplicationManager::switchApplications() {
    if (activeApplicationIndex < 0 && numberOfApplications > 0) {
        // TODO: Check for nullptr
        applications[0]->enable();
        activeApplicationIndex = 0;
        return;
    }

    //if (applicationRuntime >= activeApplication()->DefaultDisplayTime) {
    if (applicationRuntime >= (APP_DURATION*1000)) {
         AppIndex = activeApplicationIndex + 1;
  
        
        if (AppIndex >= numberOfApplications) {
            AppIndex = 0;
        }

    if (SLEEP_MODE & SLEEP_MODE_ACTIVE){
        DisplayManager::getInstance().setBrightness(10);
        if (activeApplicationIndex != 0){
            applications[activeApplicationIndex]->disable();
            applications[0]->enable();
            activeApplicationIndex = 0;
        }
    }else{
        if (AppIndex != activeApplicationIndex) {
            DisplayManager::getInstance().setBrightness(BRIGHTNESS);
            DisplayManager::getInstance().drawPixel(31,7,{255,100,0}); 
            DisplayManager::getInstance().show();  
            applications[activeApplicationIndex]->disable();

            applications[AppIndex]->enable();
            DisplayManager::getInstance().wipe({500});
            activeApplicationIndex = AppIndex;
        }
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
