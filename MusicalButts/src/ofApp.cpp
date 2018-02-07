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
    //players[0].play();
}

//--------------------------------------------------------------
void ofApp::update(){
    touchBoard.update();
    vector<bool> touches = touchBoard.getTouchStatus();
    for(int i = 0; i < players.size(); i++) {
       //cout<<i <<": "<<touches[i]<<" ,";
        if(touches[i]) {
            cout<<"Touched!";
            if(!players[i].isPlaying()) {
                cout<<"Play!";
                players[i].play();
            }
        } else {
            cout<<"Stop!";
            players[i].stop();
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
