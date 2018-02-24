#ifndef AwtrixSettings_h
#define AwtrixSettings_h

#include <ArduinoJson.h>

class AwtrixSettings {
    private:
        // Singleton setup
        AwtrixSettings(){}
        AwtrixSettings(AwtrixSettings const&);
        void operator = (AwtrixSettings const&);

        void loadDefaultSettings();
        
        bool saveSettings();
        JsonObject* dataObject;

        const size_t bufferSize = JSON_OBJECT_SIZE(12);
        const String filename = "/config.json";

    public:
        void parseSettings(char []);
        static AwtrixSettings& getInstance() {
            static AwtrixSettings instance;
            return instance;
        }

        template <typename TValue, typename TString>
        bool set(const TString& key, const TValue& value) {
            dataObject->set(key, value);
            //saveSettings();
        }

        template <typename TValue, typename TString>
        typename Internals::JsonVariantAs<TValue>::type get(const TString& key){
            return dataObject->get<TValue>(key);
        }
        void initialise();
};

#endif
