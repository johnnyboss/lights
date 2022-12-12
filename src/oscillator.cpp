#include "oscillator.h"

void oscillator::setup (int sampRate)
{
    sampleRate = sampRate;
    type = sineWave;
    isPlaying = false;
    setVolume(1);
}

void oscillator::start()
{
    startTime = ofGetElapsedTimef();
    isPlaying = true;
}

void oscillator::stop()
{
    isPlaying = false;
}

void oscillator::setFrequency(float freq)
{
    frequency = freq;
    phaseAdder = ((float)(TWO_PI) / frequency)/60.0;
    //std::cout<<"Phase adder "<<phaseAdder<<std::endl;
    //std::cout<<phaseAdder<<std::endl;
}

void oscillator::setVolume(float vol)
{
    volume = vol;
}
float oscillator::getVolume()
{
    return volume;
}
float oscillator::getFrequency()
{
    return frequency;
}

float oscillator::getSample()
{
    if(isPlaying)
    {
        phase = (ofGetElapsedTimef() - startTime)* 60/frequency;
        while (phase>TWO_PI) 
        {
            phase-=TWO_PI;
        }
        
        if (type == sineWave) 
        {
            return sin((ofGetElapsedTimef() - startTime)* 60/frequency ) * volume;
        } 
        else if (type==squareWave)
        {
            return (sin(phase) > 0 ? 1 : -1) * volume;
        } 
        else if (type==triangleWave)
        {
            float pct = phase / TWO_PI;
            return (pct < 0.5 ? ofMap(pct, 0, 0.5, -1, 1) : ofMap(pct, 0.5, 1.0, 1, -1)) * volume;
        } 
        else if (type==sawWave)
        {
            float pct = phase / TWO_PI;
            return ofMap (pct, 0, 1, -1, 1) * volume;
        } 
        else if (type==inverseSawWave)
        {
            float pct = phase / TWO_PI;
            return ofMap(pct, 0, 1, 1, -1) * volume;
        }
    }
    return 0;
}