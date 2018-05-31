//
//  spectrumFinder.hpp
//  superShape
//
//  Created by cafe on 15/02/2018.
//

#ifndef spectrumFinder_hpp
#define spectrumFinder_hpp

#include "ofMain.h"

class spectrumFinder {
public:
    vector<ofColor> getColorsFromImage(ofImage img);
    void drawColors(vector<ofColor> cols, int _x, int _y, float limit);
    
private:
    float getColorDistance(ofColor col1, ofColor col2);
    ofColor getBlendedColor(ofColor col1, int w1, ofColor col2, int w2);    
};

#endif /* spectrumFinder_hpp */
