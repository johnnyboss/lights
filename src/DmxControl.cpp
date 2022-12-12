#include "DmxControl.h"

void DmxControl::setup(int _nChannels, int _startAddress)
{
    dmx.connect(0, _nChannels);
    nChannels = _nChannels;
    startAddress = _startAddress;
    for (int i = 0; i < 24; i++) //DMX starts at channel 1
    {
        channels.push_back(Channel(_startAddress + i, true));
    }
    updateAll();
    dmx.update(true); // black on startup
    isControlON = true;
}

void DmxControl::update()
{
    if(dmx.isConnected() && isControlON) 
    {
		dmx.update();
	}
}

void DmxControl::updateAll(bool clear)
{
    for(auto c : channels)
    {
        if(!clear)
            dmx.setLevel(c.number, c.value);
        else
            dmx.setLevel(c.number, 0);
    }
    dmx.update();
}
void DmxControl::updateChannel(int channel, float value)
{
    float val = ofMap(value,channels[channel].minValue, channels[channel].maxValue, channels[channel].minRange, channels[channel].maxRange,true);
    //level = ofMap(scaledVol, 0.0, 0.5, 0, 120);
    //std::cout<<"Update dmx with "<<val<<std::endl;
    //std::cout<<"Update channel "<<channel<<" with "<<value<<std::endl;

    dmx.setLevel(channels[channel].number, val);
}

void DmxControl::disconnect()
{
    dmx.update(true); // black on shutdown
    isControlON = false;
}
void DmxControl::connect()
{
    isControlON = true;
}