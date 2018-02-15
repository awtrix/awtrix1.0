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
        int numberOfApplications = 0;
        IApplication** applications;

        int activeApplicationIndex;

        void addApplication();
        void switchApplications();
        
    public:
        static ApplicationManager& getInstance() {
            static ApplicationManager instance;
            return instance;
        }

        void loop();
        IApplication* activeApplication();
};

#endif
