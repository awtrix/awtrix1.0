#ifndef AwtrixPetApplication_h
#define AwtrixPetApplication_h

#include <IApplication.h>
#include <../Awtrix/config.h>


class PetApp : public IApplication
{
    private:
        AwtrixColor eyeColor = {255,255,255};      
    public:
        void render(DisplayManager&) override;
};

#endif
