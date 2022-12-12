#include "sequencer.h"

void sequencer::setup()
{
    ofSetBackgroundColor(48);
	//STEP SEQUENCER
	SEQ.setup();
	SEQ.set_SHOW_Gui(true);
	SEQ_Gui_Customize();

	//------------------------------------------------------

	//LOCAL TARGET NOTES PARAMS (toggle bools) & GUI MONITOR

	//optional customize
	ofJson confg_Cont =
	{
		{"width", 40}
	};
	ofJson confg_Button =
	{
		{"type", "fullsize"},
		{"text-align", "right"},
		{"height", 21},
		//{"width", 100},
		//{"text-align", "center"},
	};

	gui_Notes = gui_Panel_Notes.addContainer();
	gui_Notes->setName("LOCAL NOTES");
	gui_Notes->setConfig(confg_Cont);

	//notes_paramsGroup.setName("NOTES PARAMS");//CALLBACKS MODE B

	//--

	//ofApp local params. bool/toggles target receivers from sequencer
	// for (int col = 0; col < NUM_SEQ_NOTES; col++)
	// {
	// 	//define param
	// 	string nStr = ofToString(col + 1);
	// 	notes_params[col].set(nStr, false);

	// 	//add param to gui panel
	// 	gui_Notes->add<ofxGuiToggle>(notes_params[col]);
	// 	//notes_paramsGroup.add(notes_params[col]);//CALLBACKS MODE B

	// 	//customize added button
	// 	gui_Notes->getControl(nStr)->setConfig(confg_Button);
	// }

	//layout and theme
	gui_Notes->setPosition(880, 10);
	gui_Notes->loadTheme("theme/theme_bleurgh.json");

	//--

	//CALLBACKS MODE A:
	//listener to directly check inside class ofxStepSequencer and receive states
	ofAddListener(SEQ.TARGET_NOTES_paramsGroup.parameterChangedE(), this, &sequencer::Changed_SEQ_NOTES);

}

void sequencer::show(bool _show)
{
	SEQ.presetsManager.setVisible_Gui(_show);//show
	SEQ.presetsManager.setVisible_ClickerPanel(_show);//show
	SEQ.set_SHOW_Gui(_show);

}
//--------------------------------------------------------------
void sequencer::SEQ_Gui_Customize()
{
	//optional customize layout

	//THEME
	int grid_w = 1200;
	int grid_h = 1000;
	SEQ.setPosition_GridSequencer(465, 10, grid_w, grid_h);
	SEQ.setPosition_Gui(220, 5);

	//BEAT CLOCK TRANSPORT
	//SEQ.setPosition_BeatClock(5, 5);

	int squares_w = 200;
	int ball_radius = 30;
	int px = 5;
	int py = 5;
	//SEQ.setPosition_CLOCK_Gui(px, py, squares_w);//main gui. titled as 'ofxStepSequencer'
	//SEQ.setPosition_CLOCK_Squares(px, py + 630, squares_w);//beat squares
	//SEQ.setPosition_CLOCK_Ball(px + squares_w * 0.5 - ball_radius, py + 830, ball_radius);//beat ball for visual feedback

	//PRESET MANAGER
	//SEQ.presetsManager.set_GUI_position(465, 350 + grid_w / 9 + 10);//gui titled as 'SEQ PATTERNS'
	SEQ.presetsManager.set_GUI_position(50, 500);//gui titled as 'SEQ PATTERNS'
	SEQ.presetsManager.setPosition_ClickerPanel(50, 700, grid_w / 9);//mouse clicker preset selector
	SEQ.presetsManager.setVisible_ClickerPanel(false);//show
	SEQ.presetsManager.setVisible_Gui(false);//show

	//-

	//TODO: customize data folder. startup buggy..
	//SEQ.presetsManager.set_pathKit_Folder("patterns/kit_1");

	//load last GRID settings
	//path = "SEQ_default.json";
	//SEQ.load_JSON(path);
}

//--------------------------------------------------------------
void sequencer::update()
{
	SEQ.update();
	isPlaying = SEQ.isPlaying;
	// for(int i = 0; i < NUM_SEQ_NOTES; i++)
	// {
	// 	std::cout<<"Note "<<i<<" : "<<notes_params[i]<<std::endl;
	// }
}

//--------------------------------------------------------------
void sequencer::draw()
{
	SEQ.draw();//grid sequencer
	SEQ.draw_CLOCK();//visual feedback: beat ball, beat squares and text info
}

//--------------------------------------------------------------
void sequencer::exit()
{
	//save current preset steps
	//SEQ.save_JSON(path);

	SEQ.exit();
	ofRemoveListener(SEQ.TARGET_NOTES_paramsGroup.parameterChangedE(), this, &sequencer::Changed_SEQ_NOTES);
}


//--------------------------------------------------------------
//CALLBACKS MODE A:
//listener to check inside class ofxStepSequencer
void sequencer::Changed_SEQ_NOTES(ofAbstractParameter& e)
{
	hasNewStep = true;
	string name = e.getName();
	int noteNum = ofToInt(name);
	bool state = false;

	if (e.type() == typeid(ofParameter<bool>).name())
	{
		ofParameter<bool> p = e.cast<bool>();
		state = p;
		ofLogVerbose("ofApp") << "Changed_SEQ_NOTES: " << name << (p ? " ON" : " OFF");
		notes_params[noteNum] = state;

		//-

		//here you can trig midi notes_params i.e.
		//pd.sendNoteOn(midiChan, noteFirst + noteNum, (int)state?127:0);
	}
}