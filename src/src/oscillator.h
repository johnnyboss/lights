#include "ofMain.h"

class oscillator{
    
public:
    
    enum
    {
        sineWave, squareWave, triangleWave, sawWave, inverseSawWave
    } waveType;
    
    int type;
    
    int sampleRate;
    float frequency;
    float volume;
    float phase;
    float phaseAdder;
    float startTime;
    bool isPlaying;

    void start();
    void stop();
    void setup (int sampRate);
    void setFrequency (float freq);
    void setVolume (float vol);
    float getFrequency();
    float getVolume();
    float getSample();
    
};