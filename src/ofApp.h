#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "oscillator.h"
#include "sequencer.h"
# include "DmxControl.h"
#include "guiController.h"
#include "mockStage.h"
#include "ofxOsc.h"
#include "strobes.h"
#include "ofEvents.h"

#define PORT 7400

class ofApp : public ofBaseApp, public ofxMidiListener
{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void dealwithOscs();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void stripSeqTogglePressed();
		void newMidiMessage(ofxMidiMessage &eventArgs);
		void dealWithMidi(float pitch, float val);
		float calcFreq(float val);

		vector<oscillator> osc;

		bool redMasterOscOn, blueMasterOscOn;
		bool redMasterStrobeOn, blueMasterStrobeOn;
		oscillator redMasterOsc;
		oscillator blueMasterOsc;

		int activeOsc;
		float intensity;
		//GUI
		ofxPanel gui;
		ofxToggle seqToggle, guiToggle, midiToggle, randomBrightToggle, redActive, blueActive, oscReceiver;

		ofxToggle knobDebug, allRed, allBlue, oscillatorToggle, cubeStrobeToggle;
		ofxFloatSlider minSeqBrightness, maxSeqBrightness, redFade, blueFade;
		ofxFloatSlider minRedBrightness, maxRedBrightness, minBlueBrightness, maxBlueBrightness;

		//ofxFloatSlider minRedBrightness, maxRedBrightness, minBlueBrightness, maxBlueBrightness;

		bool stripSeqActive;
		bool allRedActive, allBlueActive;

		bool masterRedController, masterBlueController;
		bool masterRedActive, masterBlueActive;
		guiController controller;
		bool DMXneedsUpdate;

		DmxControl dmx;

		sequencer seq;

		strobes cubeStrobes;

		ofxMidiIn midiIn;
		std::vector<ofxMidiMessage> midiMessages;
		std::size_t maxMessages = 10; //< max number of messages to keep track of
		vector<float> pads;

		ofxOscReceiver receiver;

		ofArduino ard;
};
