#ifndef IApplication_h
#define IApplication_h

class IApplication
{
    public:
        virtual ~IApplication() {}
        
        virtual void enable() { }
        virtual void disable() { }
        virtual void tick(unsigned long) { }
        
        virtual void render() = 0;
};

#endif