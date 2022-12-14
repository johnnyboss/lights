# include "ofxMidi.h"
#include "ofMain.h"

class guiController: public ofxMidiListener
{
public:
    void setup();
    void drawDebug();
    void close();
    void newMidiMessage(ofxMidiMessage& eventArgs);
    ofxMidiIn midiIn;

    bool hasNewValue;
    vector<int> newInputs;

    vector<float> inputs;
    vector<ofRectangle> pads;
    std::vector<ofxMidiMessage> midiMessages;
    std::size_t maxMessages = 10; //< max number of messages to keep track of

    vector<bool> toggles;
    vector<bool> buttons;

    bool init;
    bool isconnected;
};