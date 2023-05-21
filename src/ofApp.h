#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "AlembicRenderer.hpp"
#include "oscWorkhorse.hpp"
#include "ofxNDI.h"
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

    //NDI
    ofxNDIsender ndiSender;        // NDI sender
    std::string senderName;        // Sender name
    unsigned int senderWidth = 0;  // Width of the sender output
    unsigned int senderHeight = 0;

    bool bReadback = true;
    bool bAsync = true;
    double framerate = 60.0;

    ofCamera cam;
    
    ofxGui gui;
    
    ofxGuiPanel* panel;
    
    float playbackTime;
};
