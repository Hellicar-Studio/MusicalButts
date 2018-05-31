#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    touchBoard.setup(0);
    
    ofxNestedFileLoader loader;
    
    for(int j = 0; j < 4; j++) {
        vector<string> audioPaths = loader.load("sounds/seat" + ofToString(j+1));
        vector<ofSoundPlayer> playersTemp;
        for(int i = 0; i < audioPaths.size(); i++) {
            cout<<audioPaths[i]<<endl;
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
    
    ofImage img;
    img.load("Images/Tapestry.jpg");
    spectrumFinder f;
    cols = f.getColorsFromImage(img);
    
    for(int i = 0; i < 200; i++) {
        Column col;
        col.height = ofGetHeight() / 4;
        col.baseHeight = col.height;
        col.col = cols[int(ofRandom(cols.size()))];
        col.order = i;
        topCols.push_back(col);
    }
    
    for(int i = 0; i < 200; i++) {
        Column col;
        col.height = ofGetHeight() / 4;
        col.baseHeight = col.height;
        col.col = cols[int(ofRandom(cols.size()))];
        col.order = i + 100;
        botCols.push_back(col);
    }
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Settings", settingsPath);
    gui.add(numCols.set("Num Cols", 5, 1, 200));
    gui.add(noiseSpeed.set("Noise Speed", 0.0, 0.0, 10.0));
    gui.add(noiseScale.set("Noise Scale", 20.0, 0.0, 500.0));
    gui.add(noiseResolution.set("Noise Res", 0.5, 0.0, 1.03));
    gui.add(baseHeight.set("Base Col Height", ofGetHeight()/4, 0.0, ofGetHeight()));
    gui.add(bufferSize.set("Buffer Size", 128, 0.0, ofGetHeight()));
    gui.add(colorLerpSpeed.set("Color Speed", 0.005, 0.0, 1.0));
    gui.add(timeBetweenSwaps.set("Color Duration", 30.0, 1.0, 180.0));
    
    gui.loadFromFile(settingsPath);
	
	numCols = 1;
    
    ofBackground(0);
    
    topBuffer.allocate(ofGetWidth(), ofGetHeight());
    botBuffer.allocate(ofGetWidth(), ofGetHeight());
    viewBuffer.allocate(ofGetWidth(), ofGetHeight());
    
    mix.load("shaders/mix");
    blur.load("shaders/blur");
    
    topCap.addVertex(ofVec3f(0, 0, 0));
    topCap.addVertex(ofVec3f(0, 10, 0));
    topCap.addVertex(ofVec3f(10, 10, 0));
    topCap.addVertex(ofVec3f(10, 0, 0));
    topCap.addIndex(0);
    topCap.addIndex(1);
    topCap.addIndex(2);
    topCap.addIndex(0);
    topCap.addIndex(2);
    topCap.addIndex(3);
    topCap.addColor(ofColor(255));
    topCap.addColor(ofColor(0));
    topCap.addColor(ofColor(0));
    topCap.addColor(ofColor(255));
    
    topCap.setMode(OF_PRIMITIVE_TRIANGLES);
    
    botCap.addVertex(ofVec3f(0, 0, 0));
    botCap.addVertex(ofVec3f(0, 10, 0));
    botCap.addVertex(ofVec3f(10, 10, 0));
    botCap.addVertex(ofVec3f(10, 0, 0));
    botCap.addIndex(0);
    botCap.addIndex(1);
    botCap.addIndex(2);
    botCap.addIndex(0);
    botCap.addIndex(2);
    botCap.addIndex(3);
    botCap.addColor(ofColor(0));
    botCap.addColor(ofColor(255));
    botCap.addColor(ofColor(255));
    botCap.addColor(ofColor(0));
    
    botCap.setMode(OF_PRIMITIVE_TRIANGLES);
    
    lastSwapTime = ofGetElapsedTimef();
	
	ofHideCursor();
    
    showGui = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    touchBoard.update();
    vector<bool> touches = touchBoard.getTouchStatus();
    for(int i = 0; i < players.size(); i++) {
        players[i].update();
        if(touches[i]) {
            if(!players[i].isPlaying()) {
                players[i].play();
                string time = ofToString(ofGetElapsedTimef());
                xml.addValue("Event", ofToString(i) + "*" + ofToString(players[i].index) + "*On*" + time);
                xml.saveFile("record.xml");
                numCols++;
            }
        } else {
            if(players[i].isPlaying()) {
                players[i].stop();
                string time = ofToString(ofGetElapsedTimef());
                xml.addValue("Event", ofToString(i) + "*" + ofToString(players[i].index) + "*Off*" + time);
                xml.saveFile("record.xml");
				numCols--;
            }
        }
    }
    for(int i = 0; i < topCols.size(); i++) {
        topCols[i].baseHeight = baseHeight;
        topCols[i].update(noiseSpeed, noiseScale, noiseResolution, colorLerpSpeed);
    }
    for(int i = 0; i < botCols.size(); i++) {
        botCols[i].baseHeight = baseHeight;
        botCols[i].update(noiseSpeed, noiseScale, noiseResolution, colorLerpSpeed);
    }
    
    if(ofGetElapsedTimef() > lastSwapTime + timeBetweenSwaps) {
        for(int i = 0; i < topCols.size(); i++) {
            topCols[i].nextCol = cols[int(ofRandom(cols.size()))];
        }
        for(int i = 0; i < botCols.size(); i++) {
            botCols[i].nextCol = cols[int(ofRandom(cols.size()))];
        }
        lastSwapTime = ofGetElapsedTimef();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    topBuffer.begin();
    ofClear(0);
    for(int i = 0; i < topCols.size(); i++) {
        Column col = topCols[i];
        ofSetColor(col.col);
        ofDrawRectangle(i * topBuffer.getWidth() / numCols, 0, topBuffer.getWidth() / numCols, col.height);
        ofPushMatrix();
        ofTranslate(i * topBuffer.getWidth() / numCols, col.height);
        ofScale(topBuffer.getWidth() / numCols / 10, 0.1);
        topCap.setColor(0, col.col);
        topCap.setColor(3, col.col);
        topCap.draw();
        ofPopMatrix();
    }
    topBuffer.end();
    
    botBuffer.begin();
    ofClear(0);
    for(int i = 0; i < botCols.size(); i++) {
        Column col = botCols[i];
        ofSetColor(col.col);
        ofDrawRectangle(i * botBuffer.getWidth() / numCols, botBuffer.getHeight() - col.height, botBuffer.getWidth() / numCols, col.height);
        ofPushMatrix();
        ofTranslate(i * botBuffer.getWidth() / numCols, botBuffer.getHeight() - col.height);
        ofScale(topBuffer.getWidth() / numCols / 10, 0.1);
        botCap.setColor(1, col.col);
        botCap.setColor(2, col.col);
        botCap.draw();
        ofPopMatrix();
    }
    botBuffer.end();
    
    viewBuffer.begin();
    mix.begin();
    mix.setUniformTexture("top", topBuffer, 0);
    mix.setUniformTexture("bot", botBuffer, 1);
    ofDrawRectangle(0, 0, viewBuffer.getWidth(), viewBuffer.getHeight());
    mix.end();
    viewBuffer.end();
    
    viewBuffer.draw(0, 0);
    
    if(showGui) {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        for(int i = 0; i < topCols.size(); i++) {
            topCols[i].nextCol = cols[int(ofRandom(cols.size()))];
        }
        for(int i = 0; i < botCols.size(); i++) {
            botCols[i].nextCol = cols[int(ofRandom(cols.size()))];
        }
    }
    if(key == 'g') {
        showGui = !showGui;
		if(showGui) {
			ofShowCursor();
		} else {
			ofHideCursor();
		}
    }
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
