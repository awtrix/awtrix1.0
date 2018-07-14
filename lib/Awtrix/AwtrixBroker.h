#ifndef AwtrixBroker_h
#define AwtrixBroker_h
#include <AwtrixWiFi.h>
#include "config.h"
#include <DisplayManager.h>
#include <Settings.h>
#include <MQTT.h>


class AwtrixBroker
{
    private: 
    public:
        static AwtrixBroker& getInstance() {
            static AwtrixBroker instance;
            return instance;
        }
        String doJob(String,String);
        void log(String);
};

#endif
