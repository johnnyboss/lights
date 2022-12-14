#include "mockStage.h"

void mockStage::setup()
{
    // for(int i = 0; i < 24; i++)
    // {
    //     ledStrips.push_back(0)
    // }
    // for(int i = 0; i < 12; i++)
    // {
    //     ledTubes.push_back(0)
    // }
}

void mockStage::updateLeds()
{
    
}

void mockStage::updateStrips(vector<float> channels)
{
    for(int i = 0; i < channels.size(); i++)
    {
        std::cout<<"Strip "<<i<<" value: "<<channels[i]<<std::endl;
    }
    ledStrips = channels;
    
}

void mockStage::draw()
{
    for(int i = 0; i < ledStrips.size(); i++)
    {
        if(i < 12)
            ofSetColor(255*ledStrips[i], 0, 0);
        else
            ofSetColor(0,0,255*ledStrips[i]);
        ofDrawRectangle(20 + 35*i, ofGetHeight() - 100, 30, 30);
    }

    // for(int i = 0; i < ledTubes.size(); i++)
    // {
    //     ofSetColor(255*ledTubes[i], 0, 0);
    //     ofDrawRectangle(20 + 25*i, 50, 20, 20);
    // }
}