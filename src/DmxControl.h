#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
using namespace std;

struct Channel
{
    int number;
    bool isActive;
    float value, minRange, maxRange, minValue,maxValue;
    string effect;
    Channel(int _number, bool _isActive)
    {
        number = _number;
        isActive = _isActive;
        minRange = 0;
        maxRange = 254;
        minValue = 0.0;
        maxValue = 1;
        value = 0;
    }
    void setValue(float _value)
    {
        value = _value;
    }
    void setActivate(bool _isActive)
    {
        isActive = _isActive;
    }
    void setMinRange(float _minRange)
    {
        minRange = _minRange;
    }
    void setMaxRange(float _maxRange)
    {
        maxRange = _maxRange;
    }

    void setMinValue(float _minValue)
    {
        minValue = _minValue;
    }

    void setMaxValue(float _maxValue)
    {
        maxValue = _maxValue;
    }
};

class DmxControl
{
    public:
        void setup(int _nChannels, int _startAddress);
        void update();
        void updateChannel(int channel, float value);
        void disconnect();
        void connect();
        void updateAll(bool clear = false);
    private:
        string deviceID;
        int nChannels, startAddress;
        map<int,float> minRange;
        map<int,float> maxRange;
        map<int,float> minValue;
        map<int,float> maxValue;
        vector<Channel> channels;
        ofxDmx dmx;
        bool isControlON;
        bool needsUpdate;
};