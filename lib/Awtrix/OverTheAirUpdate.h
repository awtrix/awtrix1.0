#ifndef OverTheAirUpdate_h
#define OverTheAirUpdate_h

class OverTheAirUpdate
{
    public:
        void setup();
        void loop();
        bool isUpdating();

    private:
        bool updating = false;
};

#endif
