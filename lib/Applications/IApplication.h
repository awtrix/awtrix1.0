#ifndef IApplication_h
#define IApplication_h

#include <DisplayManager.h>

class IApplication
{
    protected:


    public:
        unsigned long const DefaultDisplayTime = 30000l;

        virtual ~IApplication() {}
        virtual void disable() {}
        virtual void update() {}
        virtual void render(DisplayManager&) = 0;
        virtual void enable() {
           
        }
};

#endif
