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
    abcGroup.add(shaderScale.set("/shader/scale", 0.5, 0, 10));
    abcGroup.add(shaderT.set("/shader/t", 0.5, 0, 100));
    abcGroup.add(baseColor.set("/shader/color", ofFloatColor(1, 0, 0, 1), ofFloatColor(0, 0, 0, 0), ofFloatColor(1, 1, 1, 1)));

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
        if (b.getAddress() == "/shader/color") {
            baseColor.set(ofFloatColor(b.getArgAsFloat(0), b.getArgAsFloat(1), b.getArgAsFloat(2), b.getArgAsFloat(3)));
        }
        if (b.getAddress() == "/shader/scale") {
            shaderScale.set(floor(ofMap(b.getArgAsFloat(0), 0.0, 1.0, shaderScale.getMin(), shaderScale.getMax(), true)));
        }
        if (b.getAddress() == "/shader/t") {
            shaderT.set(floor(ofMap(b.getArgAsFloat(0), 0.0, 1.0, shaderT.getMin(), shaderT.getMax(), true)));
        }
    }
}
