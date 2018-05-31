//
//  spectrumFinder.cpp
//  superShape
//
//  Created by cafe on 15/02/2018.
//

#include "spectrumFinder.hpp"

//--------------------------------------------------------------
bool compareNumColors(pair<ofColor, int> col1, pair<ofColor, int> col2) {
    return col1.second < col2.second;
}

//--------------------------------------------------------------
vector<ofColor> spectrumFinder::getColorsFromImage(ofImage img) {
    vector<pair<ofColor, int>> colorBins;
    
    float distTolerance = 30.0;
    
    for (int x = 0; x < img.getWidth(); x += img.getWidth()/100) {
        for (int y = 0; y < img.getHeight(); y += img.getHeight() / 100) {
            ofColor col = img.getColor(x, y);
            bool binned = false;
            for (auto it = colorBins.begin(); it != colorBins.end(); it++) {
                if (getColorDistance(col, it->first) < distTolerance) {
                    it->first = getBlendedColor(it->first, it->second, col, 1);
                    it->second++;
                    binned = true;
                    break;
                }
            }
            if (!binned) {
                // Create new bin
                pair<ofColor, int> p;
                p.first = col;
                p.second = 1;
                colorBins.push_back(p);
            }
        }
    }
    
    
    std::sort(colorBins.begin(), colorBins.end(), compareNumColors);
    
    vector<ofColor> cols;
    for(int i = 0; i < colorBins.size(); i++) {
        cols.push_back(colorBins[i].first);
    }
    
    return cols;
}

//--------------------------------------------------------------
void spectrumFinder::drawColors(vector<ofColor> cols, int _x, int _y, float limit) {
    float x = _x;
    float y = _y;
    for(int i = 0; i < cols.size(); i++) {
        ofSetColor(cols[i]);
        ofDrawRectangle(x, y, 20, 20);
        x += 20;
        if(x+20 > limit) {
            x = _x;
            y += 20;
        }
    }
}

//--------------------------------------------------------------
float spectrumFinder::getColorDistance(ofColor col1, ofColor col2) {
    float r = col2.r - col1.r;
    float g = col2.g - col1.g;
    float b = col2.b - col1.b;
    
    float dist = sqrt(r*r + g*g + b*b);
    
    return dist;
}

//--------------------------------------------------------------
ofColor spectrumFinder::getBlendedColor(ofColor col1, int w1, ofColor col2, int w2) {
    float r = col2.r * w2 + col1.r * w1;
    float g = col2.g * w2 + col1.g * w1;
    float b = col2.b * w2 + col1.b * w1;
    
    r /= (w1 + w2);
    g /= (w1 + w2);
    b /= (w1 + w2);
    
    return ofColor(r, g, b);
}
