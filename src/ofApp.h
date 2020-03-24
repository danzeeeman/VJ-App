#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "AlembicRenderer.hpp"
#include "oscWorkhorse.hpp"
#include "ofxSyphon.h"
class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    
    void setupGui();
    void loadAbcFiles();
    vector<string> abcPaths;
    int currentIndex;
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
    
    //ABC
    AlembicRenderer abcRenderer;
    //OSC
    oscWorkhorse osc;
    //RENDER VIEWPORT
    ofRectangle mViewPort;
    //RENDER FBO

    //SYPHON
    ofxSyphonServer syphon;
    ofCamera cam;
    
    ofxGui gui;
    
    ofxGuiPanel* panel;
    
    float playbackTime;
};
