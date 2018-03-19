#ifndef AwtrixSettings_h
#define AwtrixSettings_h

#include <ArduinoJson.h>

class AwtrixSettings {
    private:
        // Singleton setup

        AwtrixSettings(){}       
        AwtrixSettings(AwtrixSettings const&);
        void operator = (AwtrixSettings const&);
        const String filename = "/config.json";
        
        
    public:
       
        static AwtrixSettings& getInstance() {
            static AwtrixSettings instance;
            return instance;
        }

        void loadSettings();
        void restoreSettings();
        bool saveSettings();
        void parseSettings(String);
};

#endif
