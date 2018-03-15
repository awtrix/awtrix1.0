#ifndef AwtrixApplicationManager_h
#define AwtrixApplicationManager_h

#include <IApplication.h>

class ApplicationManager
{
    private:
        // Singleton setup
        ApplicationManager() {}
        ApplicationManager(ApplicationManager const&);
        void operator = (ApplicationManager const&);

        unsigned long lastTick = 0l;

        unsigned long applicationRuntime = 0l;
        int activeApplicationIndex = -1;
        int numberOfApplications = 0;
        IApplication** applications;

        void switchApplications();
        IApplication* activeApplication();
        IApplication* getApplicationWithName(String);
        
       
    public:
        static ApplicationManager& getInstance() {
            static ApplicationManager instance;
            return instance;
        }

        void loop();
        bool addApplication(String);
};

#endif
