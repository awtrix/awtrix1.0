#ifndef AwtrixTemplateApplication_h
#define AwtrixTemplateApplication_h

#include <IApplication.h>



class TemplateApp : public IApplication
{
    private:


    public:
        
        void render(DisplayManager&) override; 
        void enable() override; 

};

#endif
