#include <guiController.h>

void guiController::setup()
{
	// print input ports to console
	// midiIn.listInPorts();

	// open port by number (you may need to change this)
	// midiIn.openPort(1);
	std::cout<<midiIn.getInPortName(1)<<std::endl;
	isconnected = midiIn.openPort(1);
	//midiIn.openPort("Teensy MIDI:Teensy MIDI");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port

	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	if(isconnected)
	{
		midiIn.ignoreTypes(false, false, false);

		// add ofApp as a listener
		midiIn.addListener(this);

		// print received messages to the console
		midiIn.setVerbose(true);
		for (int i = 0; i < 40; i++)
		{
			inputs.push_back(0.0);
		} 

		for(int i = 0; i < 4; i++)
		{
			toggles.push_back(false);
			buttons.push_back(false);
		}
	}
}

void guiController::drawDebug()
{
	for (unsigned int i = 0; i < midiMessages.size(); ++i) 
    {
		ofxMidiMessage& message = midiMessages[i];
		int x = 10;
		int y = i * 40 + 40;

		// draw the last recieved message contents to the screen,
		// this doesn't print all the data from every status type
		// but you should get the general idea
		stringstream text;
		text << ofxMidiMessage::getStatusString(message.status);
		while (text.str().length() < 16) { // pad status width
			text << " ";
		}

		ofSetColor(127);
		if (message.status < MIDI_SYSEX) {
			text << "chan: " << message.channel;
			
			if (message.status == MIDI_CONTROL_CHANGE) 
            {
				
                text << "\tctl: " << message.control;
				ofDrawRectangle(x + ofGetWidth() * 0.2, y + 12,
					ofMap(message.control, 0, 127, 0, ofGetWidth() * 0.2), 10);
				
				float val = ofMap(message.value, 0, 127, 0.0, 1.0);
				//dmx.updateChannel(message.control, val);
                
				text << "\tval: " << message.value;
				ofDrawRectangle(x + ofGetWidth() * 0.2 * 2, y + 12,
					ofMap(message.value, 0, 127, 0, ofGetWidth() * 0.2), 10);
			}
			text << " "; // pad for delta print
		}
		else {
			text << message.bytes.size() << " bytes ";
		}

		text << "delta: " << message.deltatime;
		ofSetColor(0);
		ofDrawBitmapString(text.str(), x, y);
		text.str(""); // clear
		
	}
}

void guiController::newMidiMessage(ofxMidiMessage& msg) 
{
    if(!hasNewValue)
        hasNewValue = true;
    
    // std::cout<<msg.toString()<<std::endl;
	// std::cout<<"Message on channel "<<msg.control<<" with value "<<msg.value<<std::endl;
    newInputs.push_back(msg.control);
	
    // add the latest message to the message queue
	midiMessages.push_back(msg);
    float val = ofMap(msg.value, 0, 127, 0.0, 1.0);
    inputs[msg.control] = val;

	if(msg.control > 31 && msg.control < 36)//deal with toggles
	{
		if(msg.control == 35)
		{	
			std::cout<<msg.value<<std::endl;
			if(msg.value == 1)
				toggles[0] = true;
			else
				toggles[0] = false;
		}
		else if(msg.control == 32)
		{	
			if(msg.value == 1)
				toggles[1] = true;
			else
				toggles[1] = false;
		}
		else if(msg.control == 33)
		{	
			if(msg.value == 1)
				toggles[2] = true;
			else
				toggles[2] = false;
		}
		else if(msg.control == 34)
		{	
			if(msg.value == 1)
				toggles[3] = true;
			else
				toggles[3] = false;
		}
		
	}

	if(msg.control >= 36 && msg.control < 40)//deal with buttons
	{
		if(msg.value == 1)
			buttons[39-msg.control] = true;
		else
			buttons[39-msg.control] = false;
	}
	

	// remove any old messages if we have too many
	while (midiMessages.size() > maxMessages) 
    {
		midiMessages.erase(midiMessages.begin());
	}
}

void guiController::close()
{
    midiIn.closePort();
	midiIn.removeListener(this);
}