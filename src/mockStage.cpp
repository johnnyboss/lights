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

void mockStage::updateStrips()
{

}

void mockStage::draw()
{
    for(int i = 0; i < ledStrips.size(); i++)
    {
        ofSetColor(255*ledStrips[i], 0, 0);
        ofDrawRectangle(20 + 25*i, 20, 20, 20);
    }

    for(int i = 0; i < ledTubes.size(); i++)
    {
        ofSetColor(255*ledTubes[i], 0, 0);
        ofDrawRectangle(20 + 25*i, 50, 20, 20);
    }
}