#ifndef AwtrixTemplateApplication_h
#define AwtrixTemplateApplication_h

#include <IApplication.h>



class TemplateApp : public IApplication
{
    private:
        const bool UpdateOnEnable = true;               // If true, the update function will be called once everytime the app start
        
        const unsigned long UpdateThreshold = 30000l;   // Time until the update function is called. 
                                                        // (Optional, remove line to use global threshhold)

    public:
        
        void render(DisplayManager&) override; 
        void enable() override; 
        void update() override; 
};

#endif
