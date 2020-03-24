//
//  oscWorkhorse.cpp
//  shapes
//
//  Created by Dan Moore on 2/28/20.
//

#include "oscWorkhorse.hpp"
void oscWorkhorse::setup(int port){
    receiver.setup(port);
    abcGroup.setName("OSC PORT "+ofToString(port));
    abcGroup.add(playbackPosition.set("/playback/position", 0, 0, 1));
    abcGroup.add(bScrub.set("/playback/scrub", false));
    abcGroup.add(bNext.set("/playback/next", false));
    abcGroup.add(shaderStage.set("/shader/stage", 5, 0, 10));
    abcGroup.add(abcIndex.set("/playback/index", 0, 0, 1));
    abcGroup.add(cameraIndex.set("/playback/camera", 0, 0, 10));
    abcGroup.add(baseColor.set("Color", ofFloatColor(1, 0, 0, 1), ofFloatColor(0, 0, 0, 0), ofFloatColor(1, 1, 1, 1)));

}

void oscWorkhorse::update(){
    while(receiver.hasWaitingMessages()){
        ofxOscMessage b;
        receiver.getNextMessage(b);
        if(b.getAddress() == "/playback/scrub"){
            bScrub.set(b.getArgAsBool(0));
        }
        if(b.getAddress() == "/playback/index"){
             abcIndex.set(floor(ofMap(b.getArgAsFloat(0), 0, 1, abcIndex.getMin(), abcIndex.getMax())));
         }
        if(b.getAddress() == "/playback/position"){
            playbackPosition.set(ofMap(b.getArgAsFloat(0), 0, 1, playbackPosition.getMin(), playbackPosition.getMax()));
        }
        if(b.getAddress() == "/shader/stage"){
            shaderStage.set((ofMap(b.getArgAsFloat(0), 0, 1, shaderStage.getMin(), shaderStage.getMax())));
        }
        if(b.getAddress() == "/playback/next"){
             bNext.set(b.getArgAsBool(0));
        }
        if(b.getAddress() == "/playback/camera"){
            cameraIndex.set(floor(ofMap(b.getArgAsFloat(0), 0.0, 1.0, cameraIndex.getMin(), cameraIndex.getMax(), true)));
        }
    }
}
