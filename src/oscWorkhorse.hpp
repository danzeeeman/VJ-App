//
//  oscWorkhorse.hpp
//  shapes
//
//  Created by Dan Moore on 2/28/20.
//

#ifndef oscWorkhorse_hpp
#define oscWorkhorse_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
class oscWorkhorse{
public:
    void                setup(int port);
    void                update();
    
    ofxOscReceiver      receiver;
    ofParameterGroup    abcGroup;
    ofParameter<float>  playbackPosition;
    ofParameter<int>  shaderStage;
    ofParameter<bool>   bScrub;
    ofParameter<int>    abcIndex;
    vector<string>      abcPaths;
    ofParameter<bool>   bNext;
    ofParameter<int>     cameraIndex;
    ofParameter<ofFloatColor> baseColor;
};
#endif /* oscWorkhorse_hpp */
