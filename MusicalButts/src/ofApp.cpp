#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    touchBoard.setup(0);
    
    ofxNestedFileLoader loader;
    
    vector<string> audioPaths = loader.load("sounds");
    for(int i = 0; i < audioPaths.size(); i++) {
        cout<<audioPaths[i]<<endl;
        ofSoundPlayer player;
        player.load(audioPaths[i]);
        player.setLoop(true);
        players.push_back(player);
    }
    xml.loadFile("record.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    touchBoard.update();
    vector<bool> touches = touchBoard.getTouchStatus();
    for(int i = 0; i < players.size(); i++) {
        if(touches[i]) {
            if(!players[i].isPlaying()) {
                players[i].play();
                string time = ofToString(ofGetElapsedTimef());
                cout<<"Play!"<<endl;
                xml.addValue("Event", ofToString(i) + "*On*" + time);
                xml.saveFile("record.xml");
            }
        } else {
            if(players[i].isPlaying()) {
                players[i].stop();
                string time = ofToString(ofGetElapsedTimef());
                cout<<"Stop!"<<endl;
                xml.addValue("Event", ofToString(i) + "*Off*" + time);
                xml.saveFile("record.xml");
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

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
