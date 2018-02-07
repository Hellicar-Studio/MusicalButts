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
        players.push_back(player);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    touchBoard.update();
    vector<bool> touches = touchBoard.getTouchStatus();
    for(int i = 0; i < touches.size(); i++) {
        cout<<i <<": "<<touches[i]<<" ,";
        if(touches[i]) {
            if(!players[i%players.size()].isPlaying())
                players[i%players.size()].setPaused(false);
                players[i%players.size()].play();
        } else {
            if(players[i%players.size()].isPlaying())
                players[i%players.size()].setPaused(true);
        }
    }
    cout<<endl;
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
