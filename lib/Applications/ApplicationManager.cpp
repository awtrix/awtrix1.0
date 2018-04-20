#include <ApplicationManager.h>
#include <Arduino.h>
#include <TimeApp.h>
#include <WeatherApp.h>
#include <YoutubeApp.h>
#include <DHT22App.h>
#include <PetApp.h>
#include <GolApp.h>
#include <PongApp.h>
#include <FacebookApp.h>
#include <FireApp.h>
#include <SnakeApp.h>
#include <TwitterApp.h>
#include <../Awtrix/config.h>


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

    if (name == "Pong") {
        return new PongApp();
    }

    if (name == "Snake") {
        return new SnakeApp();
    }

    return NULL;
}

void ApplicationManager::loop() {
    unsigned long thisTick = millis();
    unsigned long delta = thisTick - lastTick;

    switchApplications();
    

    IApplication* application = activeApplication();
    if (application) {
        applicationRuntime += delta;
        application->render(DisplayManager::getInstance());
  
    }

    lastTick = thisTick;
}


void ApplicationManager::loadDefault() {
    addApplication("Snake");
    addApplication("Pong");
    addApplication("Time");
    activeApplicationIndex=2;
}


void ApplicationManager::nextApplication() {
        applicationRuntime=0;
        DisplayManager::getInstance().drawPixel(31,7,{255,100,0}); 
        DisplayManager::getInstance().show();
        applications[activeApplicationIndex]->disable();

        AppIndex = activeApplicationIndex + 1;
            if (AppIndex >= numberOfApplications) {
                AppIndex = 2;
            }
        applications[AppIndex]->enable();
        DisplayManager::getInstance().wipe({500});
        activeApplicationIndex = AppIndex;
}

void ApplicationManager::switchApplications() {
    if (gamemode>0){
        if (activeApplicationIndex > 1 || game != activeApplicationIndex){
            applications[activeApplicationIndex]->disable();
            applications[game]->enable();
            activeApplicationIndex=game;
            return;
        }
        return;
    }else{
        if (activeApplicationIndex < 1){
            applications[activeApplicationIndex]->disable();
            activeApplicationIndex = 2;
            applications[activeApplicationIndex]->enable();
            return;   
    }
    
    }

    if (activeApplicationIndex < 0 && numberOfApplications > 0) {
        // TODO: Check for nullptr
        applications[2]->enable();
        activeApplicationIndex = 2;
        return;
    }

    //if (applicationRuntime >= activeApplication()->DefaultDisplayTime) {
    if (applicationRuntime >= (APP_DURATION*1000)) {
         AppIndex = activeApplicationIndex + 1;
        if (AppIndex >= numberOfApplications) {
            AppIndex = 2;
        }

    if (SLEEP_MODE){
        DisplayManager::getInstance().setBrightness(5);
        if (activeApplicationIndex > 2 ){
            applications[activeApplicationIndex]->disable();
            applications[2]->enable();
            activeApplicationIndex = 2;
        }
    }else{
        if (AppIndex != activeApplicationIndex) {
            DisplayManager::getInstance().drawPixel(31,7,{255,100,0}); 
            DisplayManager::getInstance().show();  
            applications[activeApplicationIndex]->disable();

            applications[AppIndex]->enable();
            applicationRuntime=0;
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

void ApplicationManager::removeApplication(String name) {
    int index = -1;

    // RAUSFINDEN, OB DIE GESUCHTE ANWENDUNG ÜBERHAUPT AKTIV IST!
    for (int i = 0; i < numberOfApplications; i++) {
        if (applications[i]->name.equals(name)) {
            index = i;
            break;
        }
    }

    // ANSONSTEN DIREKT AUFHÖREN
    if (index < 0) return;

    if (index == activeApplicationIndex) {
        activeApplicationIndex =2;
    }

    // HIER IST KLAR, DASS DIE ANWENDUNG DA ISST UND GELÖSCHT WERDEN KANN
    int newApplicationIndex = activeApplicationIndex;
    IApplication** newList = new IApplication*[numberOfApplications - 1];

    int newApplications = 0;
    for (int i = 0, j = 0; i < numberOfApplications; i++) {
        if (i == index) {
            applications[i]->disable();
            delete[] applications[i]; // Destructor von derr Applikation
            continue;
        }

        newList[j] = applications[i];
        j++;
    }

    delete[] applications;
    applications = newList;
    numberOfApplications = numberOfApplications - 1;

}