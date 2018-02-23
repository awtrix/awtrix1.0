#ifndef AwtrixGolApplication_h
#define AwtrixGolApplication_h

#include <IApplication.h>

class GolApp : public IApplication
{
    private:
        void gameOfLifeInit();
        const unsigned long UpdateThreshold = 30000l;
    public:
       
        void render(DisplayManager&) override;
        void update() override;
};

#endif
