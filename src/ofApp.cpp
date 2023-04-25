#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    abcRenderer.setup(1280, 720);
    abcRenderer.setCamera(cam);

    senderWidth = 1280;
    senderHeight = 720;
    senderName = "shapes";

    ndiSender.SetAspectRatio(16, 9);
    ndiSender.SetFrameRate(60);
    ndiSender.SetReadback();
    ndiSender.SetAsync();
    ndiSender.CreateSender(senderName.c_str(), senderWidth, senderHeight);
    ndiSender.SetFormat(NDIlib_FourCC_video_type_RGBA);

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
    panel->setPosition(DOM::Position(ofGetWidth() - panel->getWidth()-10, 10));
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

    ndiSender.SendImage(abcRenderer.mAbcFbo.getTexture());

    if (ndiSender.SenderCreated()) {

        std::string str;
        str = "Sending as : ["; str += senderName; str += "] (";
        str += to_string(senderWidth); str += "x"; str += to_string(senderHeight); str += ")";
        ofDrawBitmapString(str, 20, 25);
        str = "fps : "; str += to_string((int)ofGetFrameRate());
        ofDrawBitmapString(str, ofGetWidth() - 100, ofGetHeight()-10);

        // Show sending options
        ofDrawBitmapString("Sending options", 20, 48);

        str = " NDI fps  (""F"") : ";
        framerate = ndiSender.GetFrameRate();
        str += std::to_string(framerate);
        // Limit display to 2 decimal places
        size_t s = str.rfind(".");
        str = str.substr(0, s + 3);
        ofDrawBitmapString(str, 20, 66);

        str = " Async    (""A"") : ";
        str += to_string((int)ndiSender.GetAsync());
        ofDrawBitmapString(str, 20, 82);

        str = " Readback (""P"") : ";
        str += to_string((int)ndiSender.GetReadback());
        ofDrawBitmapString(str, 20, 98);

        str = " Format (""Y""""/""""R"") : ";
        if (ndiSender.GetFormat() == NDIlib_FourCC_video_type_UYVY)
            str += "YUV ";
        else
            str += "RGBA ";
        ofDrawBitmapString(str, 20, 114);

        str = " Size     (""S"") : ";
        str += to_string((int)senderWidth);
        str += "x";
        str += to_string((int)senderHeight);
        ofDrawBitmapString(str, 20, 130);

    }

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
