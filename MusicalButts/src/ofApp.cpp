#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    touchBoard.setup(0);
    
    ofxNestedFileLoader loader;
    
    for(int j = 0; j < 4; j++) {
        vector<string> audioPaths = loader.load("sounds/seat" + ofToString(j+1));
        vector<ofSoundPlayer> playersTemp;
        for(int i = 0; i < audioPaths.size(); i++) {
            ofSoundPlayer player;
            player.load(audioPaths[i]);
            player.setLoop(true);
            playersTemp.push_back(player);
        }
        soundSeat seat;
        seat.players = playersTemp;
        loader.clearPaths();
        players.push_back(seat);
    }

    xml.loadFile("record.xml");
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Volume", settingsPath);
    gui.add(volume1.set("v1", 1.0, 0.0, 1.0));
    gui.add(volume2.set("v2", 1.0, 0.0, 1.0));
    gui.add(volume3.set("v3", 1.0, 0.0, 1.0));
    gui.add(volume4.set("v4", 1.0, 0.0, 1.0));
    
    gui.loadFromFile(settingsPath);
}

//--------------------------------------------------------------
void ofApp::update(){
    touchBoard.update();
    players[0].maxVolume = volume1;
    players[1].maxVolume = volume2;
    players[2].maxVolume = volume3;
    players[3].maxVolume = volume4;

    vector<bool> touches = touchBoard.getTouchStatus();
    for(int i = 0; i < players.size(); i++) {
        players[i].update();
        if(touches[i]) {
            if(!players[i].isPlaying()) {
                players[i].play();
                string time = ofToString(ofGetElapsedTimef());
                xml.addValue("Event", ofToString(i) + "*" + ofToString(players[i].index) + "*On*" + time);
                xml.saveFile("record.xml");
            }
        } else {
            if(players[i].isPlaying()) {
                players[i].stop();
                string time = ofToString(ofGetElapsedTimef());
                xml.addValue("Event", ofToString(i) + "*" + ofToString(players[i].index) + "*Off*" + time);
                xml.saveFile("record.xml");
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
