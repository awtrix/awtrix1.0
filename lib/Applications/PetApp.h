#ifndef AwtrixPetApplication_h
#define AwtrixPetApplication_h

#include <IApplication.h>

class PetApp : public IApplication
{
    private:
        int PET_MOOD = 2;
        AwtrixColor eyeColor = {255,255,255};
        
    public:
        void render(DisplayManager&) override;
};

#endif
