#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTouchBoard.h"
#include "ofxNestedFileLoader.h"
#include "ofxXmlSettings.h"

struct soundSeat {
    soundSeat() {
        index = 0;
        volume = 0;
    };
    int index;
    float volume;
    vector<ofSoundPlayer> players;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    ofxTouchBoard touchBoard;
    vector< vector<ofSoundPlayer> > players;
    
    ofxXmlSettings xml;
		
};
