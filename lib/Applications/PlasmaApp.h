#ifndef AwtrixPlasmaApplication_h
#define AwtrixPlasmaApplication_h

#include <IApplication.h>

class PlasmaApp : public IApplication
{
    private:
        
        const unsigned long UpdateThreshold = 30000l;
    public:
        void render(DisplayManager&) override;
        void update() override;
};

#endif
