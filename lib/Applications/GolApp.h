#ifndef AwtrixGolApplication_h
#define AwtrixGolApplication_h

#include <IApplication.h>
#include <EEPROM.h> 

class GolApp : public IApplication
{
    private:

     public:
        
        void render(DisplayManager&) override;
        void enable() override;
  
};

#endif
