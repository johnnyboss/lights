#pragma once

#include "ofMain.h"
#include "ofEvents.h"

class strobe
{
    public:
    float lastTimeSwapped = 0;
    bool strobeOn= false;
    bool strobeShutdown = false;
    
    float interval = 100.0;
    
    void updateInterval(float val)
    {
        interval = val;
        if(interval < 0.01 && interval > 0)
            interval = 0.01;

        if(interval == 0)
            strobeShutdown = true;
        else
            strobeShutdown = false;
    }

    void update() 
    {
        if(ofGetElapsedTimef() - lastTimeSwapped > interval) 
        {
            strobeOn = !strobeOn;
            lastTimeSwapped = ofGetElapsedTimef();
        }
    }
};

class strobes
{
public:
    void setup();
    void setupArduino(const int & version);
    void updateStrobe(int strobe, float value);
    void updateArduino();
    void shutdownStrobes(bool state);
    ofArduino	ard;

    bool bSetupArduino, strobeShutdown;
    vector<strobe> strobes;
    map <int, int> strobePin;
};