#ifndef AwtrixSettings_h
#define AwtrixSettings_h

#include <ArduinoJson.h>

class AwtrixSettings {
    private:
        // Singleton setup

        AwtrixSettings(){}       
        AwtrixSettings(AwtrixSettings const&);
        void operator = (AwtrixSettings const&);
        const String configFile = "/config.json";
        const String settingsFile = "/settings.json";
        void setDefault();
        
        const size_t bufferSize = JSON_OBJECT_SIZE(23);
       
    public:
       
        static AwtrixSettings& getInstance() {
            static AwtrixSettings instance;
            return instance;
        }
         
        void loadSettings();
        void loadConfig();
        void restoreSettings();
        bool saveSettings();
        void parseSettings(String);
        void loadSPIFFS();
        const char getSetting(String);
        //String BLYNK_KEY = "b4473b71a6884c97a314cf9e105a15d3";

};

#endif
