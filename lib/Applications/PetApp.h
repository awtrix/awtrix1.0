#ifndef AwtrixPetApplication_h
#define AwtrixPetApplication_h

#include <IApplication.h>

class PetApp : public IApplication
{
    private:
        
        unsigned long elapsed = 0;
    public:
        void render(DisplayManager&) override;
        void tick(unsigned long) override;
        void enable() override;
};

#endif
