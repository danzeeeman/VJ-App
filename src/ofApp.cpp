#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
    abcRenderer.setup(1280, 720);
    abcRenderer.setCamera(cam);
    vector<ofColor> colorSpace;
    colorSpace.push_back(ofColor::white);
    colorSpace.push_back(ofColor::magenta);
    colorSpace.push_back(ofColor::white);
    abcRenderer.setBackgroundColors(colorSpace);
    osc.setup(1235);
    playbackTime = 0.0;
    setupGui();
    loadAbcFiles();
}
void ofApp::loadAbcFiles(){
    ofDirectory dir;
    dir.listDir(ofToDataPath("abc"));
    dir.sort();
    
    for(int i = 0;i< dir.size(); i++){
        abcPaths.push_back(dir.getPath(i));
    }
    currentIndex = 0;
    if(abcPaths.size() > 1);
        abcRenderer.load(abcPaths[currentIndex]);
    
    osc.abcIndex.setMax(abcPaths.size()-1);
}

void ofApp::setupGui(){
    panel = gui.addPanel(osc.abcGroup);
}
//--------------------------------------------------------------
void ofApp::update(){
    osc.update();
    abcRenderer.update();
    abcRenderer.setBaseColor(osc.baseColor.get());
    abcRenderer.cameraIndex = osc.cameraIndex.get();
    osc.cameraIndex.setMax(abcRenderer.cameras.size()-1);
    if(osc.bNext.get() == true){
        osc.bNext.set(false);
        currentIndex++;
              if(currentIndex >= abcPaths.size()){
                  currentIndex = 0;
              }
        ofLog()<<"load"<<abcPaths[currentIndex]<<endl;
        osc.abcIndex.set(currentIndex);
        abcRenderer.load(abcPaths[currentIndex]);
        osc.cameraIndex.set(0);
        abcRenderer.cameraIndex = osc.cameraIndex.get();
    }
    if(osc.abcIndex.get() != currentIndex){
        currentIndex = osc.abcIndex.get();
        abcRenderer.load(abcPaths[osc.abcIndex.get()]);
        osc.cameraIndex.set(0);
        abcRenderer.cameraIndex = osc.cameraIndex.get();
    }
    if(!osc.bScrub.get()){
        playbackTime = playbackTime+(1.0/24.0);
        playbackTime = fmodf(playbackTime, abcRenderer.reader.getMaxTime());
        osc.playbackPosition.set(ofMap(playbackTime, abcRenderer.reader.getMinTime(), abcRenderer.reader.getMaxTime(), 0, 1, true));
    }else{
        playbackTime = ofMap(osc.playbackPosition.get(), 0, 1, abcRenderer.reader.getMinTime(), abcRenderer.reader.getMaxTime(), true);
    }
    abcRenderer.setTime(osc.playbackPosition.get());
    abcRenderer.setStage(osc.shaderStage);
}

//--------------------------------------------------------------
void ofApp::draw(){
    abcRenderer.draw();
    abcRenderer.mAbcFbo.draw(0, 0);
    syphon.publishTexture(&abcRenderer.mAbcFbo.getTexture());

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_LEFT_SHIFT){
        abcRenderer.loadShader(ofToDataPath("shaders/shader"));
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == '='){
        currentIndex++;
        if(currentIndex >= abcPaths.size()){
            currentIndex = 0;
        }
        cout<<"load"<<abcPaths[currentIndex]<<endl;
         abcRenderer.load(abcPaths[currentIndex]);
    }
    if(key == '+'){
        currentIndex--;
        if(currentIndex < 0){
             currentIndex = abcPaths.size()-1;
         }
         abcRenderer.load(abcPaths[currentIndex]);
     }
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
