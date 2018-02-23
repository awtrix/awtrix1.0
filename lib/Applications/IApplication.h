#ifndef IApplication_h
#define IApplication_h

#include <DisplayManager.h>

class IApplication
{
    protected:
        const unsigned long UpdateThreshold = 10000l;
        const bool UpdateOnEnable = true;

        unsigned long elapsed = 0;

    public:
        unsigned long const DefaultDisplayTime = 10000l;

        virtual ~IApplication() {}
        virtual void disable() {}
        virtual void update() {}
        virtual void render(DisplayManager&) = 0;

        virtual void tick(unsigned long delta) {
            elapsed += delta;

            if (elapsed >= UpdateThreshold) {
                update();
                elapsed = 0;
            }
        }

        virtual void enable() {
            if (UpdateOnEnable) update();
        }
};

#endif
