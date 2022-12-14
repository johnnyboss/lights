#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

    midiIn.listInPorts();
    // midiIn.openPort(1);
    // midiIn.ignoreTypes(false, false, false);
	// midiIn.addListener(this);
	// midiIn.setVerbose(true);
    
    for(int i = 0; i < 8; i++)
    {
        oscillator osc1;
        osc1.setup(60);
        osc1.setFrequency(80);
        osc1.setVolume(1);
        osc.push_back(osc1);
    }
    
    redMasterOsc.setup(60);
    redMasterOsc.setFrequency(80);
    redMasterOsc.setVolume(1);
    
    blueMasterOsc.setup(60);
    blueMasterOsc.setFrequency(80);
    blueMasterOsc.setVolume(1);
    
    redMasterOscOn = false;
    blueMasterOscOn = false;
    activeOsc = 0;
//   
    controller.setup();

    receiver.setup(PORT);
    dmx.setup(24, 1);

    gui.setup();
    oscPanel.setup();
    
    seq.setup();
    
    gui.add(seqToggle.setup("SeqToggle", false));
    gui.add(guiToggle.setup("guiToggle", false));
    gui.add(midiToggle.setup("midiToggle", false));
    gui.add(redActive.setup("redActive", true));
    gui.add(blueActive.setup("blueActive", true));
    gui.add(oscReceiver.setup("oscReceiver", false));
    gui.add(oscillatorToggle.setup("oscillator", false));
    gui.add(cubeStrobeToggle.setup("cubeStrobeToggle", false));
    gui.add(randomBrightToggle.setup("randomBrightToggle", false));
    gui.add(minSeqBrightness.setup("min Seq brightness", 0, 0, 1));
    gui.add(maxSeqBrightness.setup("max Seq brightness", 1, 0, 1));

    gui.add(minRedBrightness.setup("min Red brightness", 0, 0, 1));
    gui.add(maxRedBrightness.setup("max Red brightness", 1, 0, 1));

    gui.add(minBlueBrightness.setup("min Blue brightness", 0, 0, 1));
    gui.add(maxBlueBrightness.setup("max Blue brightness", 1, 0, 1));

    // gui.add()


    gui.add(redFade.setup("redFade", 1, 0, 1));
    gui.add(blueFade.setup("blueFade", 1, 0, 1));

    gui.add(allRed.setup("allRed", false));
    gui.add(allBlue.setup("allBlue", false));

    oscPanel.add(roscSlider1.setup("rosc1", 0.5, 0, 1));
    oscPanel.add(roscSlider2.setup("rosc2", 0.5, 0, 1));
    oscPanel.add(roscSlider3.setup("rosc3", 0.5, 0, 1));
    oscPanel.add(roscSlider4.setup("rosc4", 0.5, 0, 1));

    oscPanel.add(boscSlider1.setup("bosc1", 0.5, 0, 1));
    oscPanel.add(boscSlider2.setup("bosc2", 0.5, 0, 1));
    oscPanel.add(boscSlider3.setup("bosc3", 0.5, 0, 1));
    oscPanel.add(boscSlider4.setup("bosc4", 0.5, 0, 1));

    oscPanel.add(rmasterSlider.setup("rmasterSlider", 0, 0, 1));
    oscPanel.add(bmasterSlider.setup("bmasterSlider", 0, 0, 1));

    stripSeqActive = true;
    seq.show(true);

    allRedActive = false;
    allBlueActive = false;

    ofSetFrameRate(120);
    DMXneedsUpdate = false;

    masterRedController = false;
    masterBlueController = false;

    masterRedActive = false;
    masterBlueActive  = false;

}

float ofApp::calcFreq(float val)
{   
    float freq = 61 - ofMap(val, 0, 1, 1, 60, true); 
    return freq;
}

void ofApp::dealwithOscs()
{
    if(controller.isconnected)
    {
        roscSlider1 = controller.inputs[1];
        roscSlider2 = controller.inputs[5];
        roscSlider3 = controller.inputs[9];
        roscSlider4 = controller.inputs[13];
        boscSlider1 = controller.inputs[2];
        boscSlider2 = controller.inputs[6];
        boscSlider3 = controller.inputs[10];
        boscSlider4 = controller.inputs[14];

        rmasterSlider = controller.inputs[25];
        bmasterSlider = controller.inputs[26];
    }
    // rosc1 = 
    //RED OSCS
    osc[0].setFrequency(calcFreq(roscSlider1));
    osc[1].setFrequency(calcFreq(roscSlider2));
    osc[2].setFrequency(calcFreq(roscSlider3));
    osc[3].setFrequency(calcFreq(roscSlider4));
    //BLUE OSCS
    osc[4].setFrequency(calcFreq(boscSlider1));
    osc[5].setFrequency(calcFreq(boscSlider2));
    osc[6].setFrequency(calcFreq(boscSlider3));
    osc[7].setFrequency(calcFreq(boscSlider4));

    //RED MASTER OSC
    redMasterOsc.setFrequency(calcFreq(rmasterSlider));
    //BLUE MASTER OSC
    blueMasterOsc.setFrequency(calcFreq(bmasterSlider));

    if(roscSlider1 == 0)
    {
        osc[0].stop();   
    }
    else
    {
        if(!osc[0].isPlaying)
            osc[0].start();
    }   
    if(roscSlider2 == 0)
    {
        osc[1].stop();
        for(int f = 0; f < 3; f++)
        {
            dmx.updateChannel(3 + f, 0);
        }
    }
    else
    {
        if(!osc[1].isPlaying)
            osc[1].start();
    }   
    if(roscSlider3 == 0)
    {
        osc[2].stop();
        for(int f = 0; f < 3; f++)
        {
            dmx.updateChannel(6 + f, 0);
        }
    }
    else
    {
        if(!osc[2].isPlaying)
            osc[2].start();
    }   
    if(roscSlider4 == 0)
    {
        osc[3].stop();
        for(int f = 0; f < 3; f++)
        {
            dmx.updateChannel(9 + f, 0);
        }
    }
    else
    {
        if(!osc[3].isPlaying)
            osc[3].start();
    }   
    if(boscSlider1 == 0)
    {
        osc[4].stop();
        for(int f = 0; f < 3; f++)
        {
            dmx.updateChannel(12 + f, 0);
        }
    }
    else
    {
        if(!osc[4].isPlaying)
            osc[4].start();
    }   
    if(boscSlider2 == 0)
    {
        osc[5].stop();
        for(int f = 0; f < 3; f++)
        {
            dmx.updateChannel(15 + f, 0);
        }
    }
    else
    {
        if(!osc[5].isPlaying)
            osc[5].start();
    }   
    if(boscSlider3 == 0)
    {
        osc[6].stop();
        for(int f = 0; f < 3; f++)
        {
            dmx.updateChannel(18 + f, 0);
        }
    }
    else
    {
        if(!osc[6].isPlaying)
            osc[6].start();
    }   
    if(boscSlider4 == 0)
    {
        osc[7].stop();
        for(int f = 0; f < 3; f++)
        {
            dmx.updateChannel(21 + f, 0);
        }
    }
    else
    {
        if(!osc[7].isPlaying)
            osc[7].start();
    }   

    if(rmasterSlider == 0)
    {
        redMasterOscOn = false;
        redMasterOsc.stop();

    }
    else
    {
        redMasterOscOn = true; 
        if(!redMasterOsc.isPlaying)
            redMasterOsc.start();
    }
    if(bmasterSlider == 0)
    {
        blueMasterOscOn = false;
        blueMasterOsc.stop();

    }
    else
    {
        blueMasterOscOn = true; 
        if(!blueMasterOsc.isPlaying)
            blueMasterOsc.start();
    }
        
}

//--------------------------------------------------------------
void ofApp::update()
{
    // cubeStrobes.updateArduino();
    if(controller.isconnected)
    {
        seqToggle = controller.toggles[0];
        oscillatorToggle = controller.toggles[1];
        cubeStrobeToggle = controller.toggles[2];
        oscReceiver = controller.toggles[3];

        masterRedController = controller.buttons[0];
        masterBlueController = controller.buttons[1];

        //MASTER BRIGHTNESSES
        minRedBrightness = controller.inputs[17];
        maxRedBrightness = controller.inputs[21];
        minBlueBrightness = controller.inputs[18];
        maxBlueBrightness = controller.inputs[22];
    }
    dealwithOscs();
    
    // cubeStrobes.updateStrobe(0, controller.inputs[3]);
    // cubeStrobes.updateStrobe(1, controller.inputs[7]);
    // cubeStrobes.updateStrobe(2, controller.inputs[11]);
    // cubeStrobes.updateStrobe(3, controller.inputs[4]);
    // cubeStrobes.updateStrobe(4, controller.inputs[8]);
    // cubeStrobes.updateStrobe(5, controller.inputs[12]);
    // if(cubeStrobeToggle)
    // {
    //     cubeStrobes.shutdownStrobes(false);
    // }
    // else
    // {
    //     cubeStrobes.shutdownStrobes(true);
    // }
    controller.newInputs.clear();

    seq.update();

    
    if(oscillatorToggle)
    {
        for(int i = 0; i < 8; i++)
        {
            if(osc[i].isPlaying)
            {
                DMXneedsUpdate = true;
                float dmxVal = ofMap(osc[i].getSample(), -osc[i].getVolume(), osc[i].getVolume(), 0, 1);
                for(int f = 0; f < 3; f++)
                {
                    dmx.updateChannel(i*3 + f, dmxVal);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < 8; i++)
        {
            if(osc[i].isPlaying)
            {
                osc[i].stop();
            }
        }
    }
    
    std::string msg = "";
    if(oscReceiver)
    {
        bool needsDecode = false;
        while(receiver.hasWaitingMessages())
        {
            // get the next message
		    ofxOscMessage m;
		    receiver.getNextMessage(m);
            std::cout<<"Receive message on address "<<m.getAddress()<<std::endl;
            std::cout<<m.getArgType(0)<<std::endl;
            msg = m.getArgAsString(0);
            needsDecode = true;
           
        }
        if(needsDecode)
        {
            vector<string> subdirs = ofSplitString(msg, "_");
            for(int i = 1; i < subdirs.size(); i++)
            {             
                //std::cout<<"example on band "<<i<<" : "<<dmxVal<<std::endl;
                DMXneedsUpdate = true;
                dmx.updateChannel(i-1, ofToFloat(subdirs[i]));
            }
        }
    }

    
    if(seqToggle)//USE SEQUENCER TO CONTROL LIGHTS
    {
        // if(seq.hasNewStep && seq.isPlaying)
        // {
        //     for(int i = 0; i < 24; i++)
        //     {
        //         //std::cout<<i<<" : "<<seq.notes_params[i]<<std::endl;
        //         DMXneedsUpdate = true;
        //         float lightIntensity = 0;
        //         lightIntensity = seq.notes_params[i];
        //         if(i < 12 )//check if we want to activate red
        //         {
        //             if(!redActive)
        //                 lightIntensity = 0;
        //             else
        //             {
        //                 if(randomBrightToggle)//use random values for light intensity
        //                 {
        //                     lightIntensity = lightIntensity * ofRandom(minSeqBrightness, maxSeqBrightness);
        //                 }
        //             }
        //         }
                    
        //         if(i >= 12 )//check if we want to activate blue
        //         {
        //             if(!blueActive)
        //                 lightIntensity = 0;
        //             else
        //             {
        //                 if(randomBrightToggle)//use random values for light intensity
        //                     lightIntensity = lightIntensity * ofRandom(minSeqBrightness, maxSeqBrightness);
        //             }
        //         }
        //         dmx.updateChannel(i, lightIntensity);
        //     }
        //     seq.hasNewStep = false;
        // }
    }

    if(allRed)
    {
        allRedActive = true;
        for(int i = 0; i < 12; i++)
        {
            dmx.updateChannel(i, redFade);
        }
        DMXneedsUpdate = true;
    }
    else
    {
        if(allRedActive)
        {
            for(int i = 0; i < 12; i++)
            {
                dmx.updateChannel(i, 0);
            }
            DMXneedsUpdate = true;
            allRedActive = false;
        }
    }
    
    if(allBlue)
    {
        allBlueActive = true;
        for(int i = 12; i < 24; i++)
        {
            dmx.updateChannel(i, blueFade);
        }
        DMXneedsUpdate = true;
    }
    else
    {
        if(allBlueActive)
        {
            for(int i = 12; i < 24; i++)
            {
                dmx.updateChannel(i, 0);
            }
            DMXneedsUpdate = true;
            allBlueActive = false;
        }
    }
    
    if(masterRedController)//button 0 pressed on midi
    {
        float redVal = maxRedBrightness;
        if(!masterRedActive)
            masterRedActive = true;

        if(redMasterOsc.isPlaying && controller.buttons[2])
            redVal = ofMap(redMasterOsc.getSample(), -redMasterOsc.getVolume(), redMasterOsc.getVolume(), 0, maxRedBrightness);

        for(int i = 0; i < 12; i++)
        {
            dmx.updateChannel(i, redVal);
        }
        DMXneedsUpdate = true;
    }
    else
    {
        if(masterRedActive)
        {
            for(int i = 0; i < 12; i++)
            {
                dmx.updateChannel(i, 0);
            }
            DMXneedsUpdate = true;
            masterRedActive = false;
        }
    }

    if(masterBlueController)//button 1 pressed on midi
    {
        float blueVal = maxBlueBrightness;
        if(!masterBlueActive)
            masterBlueActive = true;

        if(blueMasterOsc.isPlaying && controller.buttons[3])
            blueVal = ofMap(blueMasterOsc.getSample(), -blueMasterOsc.getVolume(), blueMasterOsc.getVolume(), 0, maxBlueBrightness);

        for(int i = 12; i < 24; i++)
        {
            dmx.updateChannel(i, blueVal);
        }
        DMXneedsUpdate = true;
    }
    else
    {
        if(masterBlueActive)
        {
            for(int i = 12; i < 24; i++)
            {
                dmx.updateChannel(i, 0);
            }
            DMXneedsUpdate = true;
            masterBlueActive = false;
        }
    }

    if(DMXneedsUpdate)
    {
        stage.updateStrips(dmx.getChannels());
        dmx.update();
        DMXneedsUpdate = false;
    }

    // //std::cout<<"Frequency "<<ofMap(mouseX, 0, ofGetWidth(), 0, 0.2, true)<<std::endl;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    gui.draw();
    oscPanel.draw();
    ofFill();
    ofSetColor(255);
    //ofRect(200,200,512, 200);
     
    ofDrawBitmapStringHighlight("frequency:  " + ofToString(osc[activeOsc].frequency), ofPoint(200,400));
    
    string type;
    // if (osc[activeOsc].type == 0) type = "sine wave";
    // if (osc[activeOsc].type == 1) type = "square wave";
    // if (osc[activeOsc].type == 2) type = "triangle wave";
    // if (osc[activeOsc].type == 3) type = "saw tooth wave";
    // if (osc[activeOsc].type == 4) type = "reverse saw tooth wave";
    
    // ofDrawBitmapStringHighlight("type:  " + type, ofPoint(200,300));
    // ofDrawBitmapStringHighlight("Current active:  " + ofToString(activeOsc), ofPoint(200,200));
    
    // for(int i = 0; i < 12; i++)
    // {
    //     ofFill();
    //     ofSetColor(255*ofMap(osc[i].getSample(), -osc[i].getVolume(), osc[i].getVolume(), 0, 1), 0, 0);
    //     ofRect(20 + i * 50, 20 , 40, 40);
    // }

    // for(int i = 12; i < 24; i++)
    // {
    //     ofFill();
    //     ofSetColor(255*ofMap(osc[i].getSample(), -osc[i].getVolume(), osc[i].getVolume(), 0, 1), 0, 0);
    //     ofRect(20 + (i-12) * 50, 70 , 40, 40);
    // }

    // ofSetColor(255,255,255);
    // ofRect(200 ,320,512, 50);
    // ofNoFill();
    // ofSetColor(0);
    // ofBeginShape();
    // for (int j = 0; j < 512; j++){
    //     ofVertex(200 + j, 320 + 75 * osc[activeOsc].getSample());
    // }
    // ofEndShape();

    seq.draw();
    controller.drawDebug();
    stage.draw();
    // for (unsigned int i = 0; i < midiMessages.size(); ++i)
	// {

	// 	ofxMidiMessage &message = midiMessages[i];
	// 	int x = 10;
	// 	int y = i * 40 + 40;

	// 	// draw the last recieved message contents to the screen,
	// 	// this doesn't print all the data from every status type
	// 	// but you should get the general idea
	// 	stringstream text;
	// 	// text << ofxMidiMessage::getStatusString(message.status);
	// 	// while (text.str().length() < 16)
	// 	// { // pad status width
	// 	// 	text << " ";
	// 	// }

	// 	ofSetColor(127);
	// 	if (message.status < MIDI_SYSEX)
	// 	{
	// 		text << "chan: " << message.channel;
	// 		if (message.status == MIDI_NOTE_ON ||
	// 			message.status == MIDI_NOTE_OFF)
	// 		{
	// 			text << "\tpitch: " << message.pitch;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2, y + 12,
	// 							ofMap(message.pitch, 0, 127, 0, ofGetWidth() * 0.2), 10);
	// 			text << "\tvel: " << message.velocity;
	// 			ofDrawRectangle(x + (ofGetWidth() * 0.2 * 2), y + 12,
	// 							ofMap(message.velocity, 0, 127, 0, ofGetWidth() * 0.2), 10);

    //             dealWithMidi(message.pitch, ofMap(message.velocity, 20, 80, 0, 255));

	// 		}
	// 		if (message.status == MIDI_CONTROL_CHANGE)
	// 		{
	// 			text << "\tctl: " << message.control;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2, y + 12,
	// 							ofMap(message.control, 0, 127, 0, ofGetWidth() * 0.2), 10);
	// 			text << "\tval: " << message.value;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2 * 2, y + 12,
	// 							ofMap(message.value, 0, 127, 0, ofGetWidth() * 0.2), 10);
	// 		}
	// 		else if (message.status == MIDI_PROGRAM_CHANGE)
	// 		{
	// 			text << "\tpgm: " << message.value;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2, y + 12,
	// 							ofMap(message.value, 0, 127, 0, ofGetWidth() * 0.2), 10);
	// 		}
	// 		else if (message.status == MIDI_PITCH_BEND)
	// 		{
	// 			text << "\tval: " << message.value;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2, y + 12,
	// 							ofMap(message.value, 0, MIDI_MAX_BEND, 0, ofGetWidth() * 0.2), 10);
	// 		}
	// 		else if (message.status == MIDI_AFTERTOUCH)
	// 		{
	// 			text << "\tval: " << message.value;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2, y + 12,
	// 							ofMap(message.value, 0, 127, 0, ofGetWidth() * 0.2), 10);
	// 		}
	// 		else if (message.status == MIDI_POLY_AFTERTOUCH)
	// 		{
	// 			text << "\tpitch: " << message.pitch;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2, y + 12,
	// 							ofMap(message.pitch, 0, 127, 0, ofGetWidth() * 0.2), 10);
	// 			text << "\tval: " << message.value;
	// 			ofDrawRectangle(x + ofGetWidth() * 0.2 * 2, y + 12,
	// 							ofMap(message.value, 0, 127, 0, ofGetWidth() * 0.2), 10);
	// 		}
	// 		text << " "; // pad for delta print
    //         text << "delta: " << message.deltatime;
	// 	ofSetColor(0);
    //     std::cout<<text.str()<<std::endl;
	// 	ofDrawBitmapString(text.str(), x, y);
	// 	text.str(""); // clear
	// 	}
	// 	// else
	// 	// {
	// 	// 	text << message.bytes.size() << " bytes ";
	// 	// }

		
	// }
	/*for (int i =)
		ofDrawRectangle(60 +, 60, 40, ofGetHeight() - 60);*/

	// ofSetColor(lights_osc[0], 0, 0);
	// ofDrawRectangle(60, 60, 40, ofGetHeight() - 60);
    //tubeSeq.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{ 

    // if(key == '1')
    // {
    //     osc[activeOsc].start();
    //     // seq.start();
    // }
    // else if(key == '+')
    // {
    //     activeOsc++;
    //     if(activeOsc > 8)
    //         activeOsc=0;
    // }
    // else if(key == '-')
    // {
    //     activeOsc--;
    //     if(activeOsc < 0)
    //         activeOsc=8;
    // }
    // else
    // {
    //     osc[activeOsc].type++;
    //     osc[activeOsc].type %= 5;
    // }

    // // switch (key)
	// // {
	// // 	//transport control
    // //     case ' ':
    // //     {
    // //         seq.SEQ.togglePlayStop();
    // //     }
    // //     break;

    // //     case OF_KEY_LEFT:
    // //         seq.SEQ.sequencer.stepBack();
    // //         break;

    // //     case OF_KEY_RIGHT:
    // //         seq.SEQ.sequencer.advance();
    // //         break;

    // //     #ifdef USE_OFXBEATCLOCK
    // //     case 't':
    // //         seq.SEQ.beatClock.tap_Trig();
    // //         break;
    // //     #endif

    // //     //helpers
    // //     case ',':
    // //         seq.SEQ.randomize();
    // //         break;

    // //     case '.':
    // //         seq.SEQ.clear();
    // //         break;

    // //     default:
    // //         break;
	// // }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    // osc[activeOsc].setFrequency( ofMap(mouseX, 0, ofGetWidth(), 1, 60, true));
    // osc[activeOsc].setVolume(ofMap(mouseY, 0, ofGetHeight(), 0, 1, true));
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 

}

void ofApp::exit() 
{
	// clean up
	controller.close();
    dmx.updateAll();
    midiIn.closePort();
	midiIn.removeListener(this);
}

void ofApp::newMidiMessage(ofxMidiMessage &msg)
{

	// if (msg.status == MIDI_PITCH_BEND)
	// {
	// 	lights_osc[0] = ofMap(msg.value, 0, 16383, 0, 255);
	// }
	/*if (msg.control > 48 && msg.control < 56)
	{
		lights[input[msg.control]] = msg.value;
	}*/
	// add the latest message to the message queue
    if(msg.deltatime > 0.005)
	    midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while (midiMessages.size() > maxMessages)
	{
		midiMessages.erase(midiMessages.begin());
	}
}

void ofApp::dealWithMidi(float pitch, float val)
{
    //MIDI MAP 44 45 46
    //         40 41 42
    //         36 37 38
    //GET Setting from somewhere
    
    if(pitch == 44 || pitch == 45 || pitch == 46)
    {
        //turnTubesOn
        if(val > 30)
        {
            std::cout<<"decimal is :"<<dec<<std::endl;

        }
    }
    else if(pitch == 40 || pitch == 41 || pitch == 42)
    {
        //TURN ON GROUND SECTION
        for(int i = 21; i < 36; i++)
        {
            //std::cout<<i<<" : "<<seq.notes_params[i]<<std::endl;
            DMXneedsUpdate = true;
            dmx.updateChannel(i-12, val);
        }
    }
    else if(pitch == 36 || pitch == 37 || pitch == 38)
    {
        //TURN ON GROUND SECTION
        for(int i = 0; i < 24; i++)
        {
            //std::cout<<i<<" : "<<seq.notes_params[i]<<std::endl;
            DMXneedsUpdate = true;
            dmx.updateChannel(i, val);
        }
    }
}