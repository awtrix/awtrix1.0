#ifndef AwtrixOverTheAirUpdate_h
#define AwtrixOverTheAirUpdate_h

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
