#ifndef IApplication_h
#define IApplication_h

#include <DisplayManager.h>

class IApplication
{
    public:
        virtual ~IApplication() {}
        
        virtual void enable() {}
        virtual void disable() {}
        virtual void tick(unsigned long) {}
        
        virtual void render(DisplayManager&) = 0;

        unsigned long const defaultDisplayTime = 10000l;
};

#endif
