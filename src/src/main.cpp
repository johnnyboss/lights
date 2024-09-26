#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"
//========================================================================
int main( ){
	// ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	
	// ofRunApp(new ofApp());

	ofGLFWWindowSettings settings;
    settings.setSize(1920, 1280);
// 	// width = 1920;
//     // settings.height = 1280;
    settings.windowMode = OF_FULLSCREEN;

    settings.setPosition(glm::vec2(0,0));
    settings.resizable = true;
//    // settings.windowMode = OF_FULLSCREEN;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
//     ofGLFWWindowSettings settings2;
    
//     settings2.setSize(1440,900);
//     settings2.setPosition(ofVec2f(0,0));
//     settings2.resizable = false;
//     shared_ptr<ofAppBaseWindow> stageWindow = ofCreateWindow(settings2);
//     stageWindow->setVerticalSync(false);

    shared_ptr<ofApp> mainApp(new ofApp);
//     ofAddListener(stageWindow->events().draw,mainApp.get(),&ofApp::drawStage);
//     // ofAddListener(stageWindow->events().update,mainApp.get(),&ofApp::updateLights);
//     // ofAddListener(stageWindow->events().keyPressed, mainApp.get(), &ofApp::dealWithKey);
//     // ofAddListener(stageWindow->events().keyReleased, mainApp.get(), &ofApp::dealWithKey);


//  //   ofAddListener(guiWindow->events().keyPressed, mainApp.get(), &testApp::dealWithKey);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();

}