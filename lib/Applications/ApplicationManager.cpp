#include <ApplicationManager.h>
#include <Arduino.h>
#include <TimeApp.h>
#include <WeatherApp.h>
#include <WeatherHumApp.h>
#include <YoutubeApp.h>
#include <DHT22App.h>
#include <PetApp.h>
#include <GolApp.h>
#include <FacebookApp.h>
#include <FireApp.h>
#include <TwitterApp.h>
#include <../Awtrix/config.h>

 struct tcp_pcb;
        extern struct tcp_pcb* tcp_tw_pcbs;
        extern "C" void tcp_abort (struct tcp_pcb* pcb);

void tcpCleanup (void) {
  while (tcp_tw_pcbs)
    tcp_abort(tcp_tw_pcbs);
}

IApplication* ApplicationManager::getApplicationWithName(String name) {
    if (name == "Time") {
        return new TimeApp();
    }

    if (name == "Weather") {
        return new WeatherApp();
    }
    
    if (name == "WeatherHum") {
        return new WeatherHumApp();
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

  
    switchApplications();
        applicationRuntime += delta;


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
        DisplayManager::getInstance().wipe();
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
         DisplayManager::getInstance().setBrightness(BRIGHTNESS);
        if (AppIndex >= numberOfApplications) {
            AppIndex = 0;
        }

    if (SLEEP_MODE){
        DisplayManager::getInstance().setSleepBrightness(5);
        if (activeApplicationIndex != 0){
            applications[activeApplicationIndex]->disable();
            applications[0]->enable();
            activeApplicationIndex = 0;
        }
    }else{
        if (AppIndex != activeApplicationIndex) {
            DisplayManager::getInstance().drawPixel(31,7,{255,100,0}); 
            DisplayManager::getInstance().show();  
 
            applications[activeApplicationIndex]->disable();

            applications[AppIndex]->enable();
            applicationRuntime=0;
            DisplayManager::getInstance().wipe();
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
