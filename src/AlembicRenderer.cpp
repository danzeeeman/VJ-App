//
//  AlembicRenderer.cpp
//  shapes
//
//  Created by Dan Moore on 2/29/20.
//

#include "AlembicRenderer.hpp"

AlembicRenderer::AlembicRenderer(){
    
}
AlembicRenderer::~AlembicRenderer(){
    
}

void AlembicRenderer::setup(int width, int height){
    mAbcFbo.allocate(width, height, GL_RGBA);
    viewport = ofRectangle(0, 0, width, height);
    mAbcFbo.begin();
    ofClear(0, 0, 0);
    mAbcFbo.end();
    loadShader(ofToDataPath("shaders/shader"));
    cubeMap.init( 1024 );
    cout<<"======== "<<endl;
    cout<<cubeMap.getWidth()<<endl;
    cout<<cubeMap.getHeight()<<endl;
    cout<<"======== "<<endl;
    sphere = ofSpherePrimitive(1000, 60);

    pos.set(10, 10, 0);
    reflections.setup(sphere.getMesh(), true);

}

void AlembicRenderer::setBackgroundColors(vector<ofColor> colors){
    gradient.reset();
    for(int i = 0 ; i < colors.size(); i++){
        gradient.addColor(colors[i]);
    }

    
    gradientFBO.allocate(2048, 2048, GL_RGBA);
    gradientFBO.begin();
      ofClear(0, 0, 0, 0);
      ofSetColor(255, 0, 255);
      gradient.drawDebug(0, 0, gradientFBO.getWidth(), gradientFBO.getHeight(), 25, true, true);
      gradientFBO.end();
    
    sphere.mapTexCoordsFromTexture(gradientFBO.getTexture());
}

void AlembicRenderer::load(string path){
    if(reader.open(path)){
        reader.setTime(0);
        cameras.clear();
        vector<string> names = reader.getNames();
        for(int i = 0 ; i < names.size(); i++){
            if(reader.get(names[i], cam)){
                cameras.push_back(names[i]);
            }
        }
        cameraIndex = 0;
        reader.get(cameras[cameraIndex], cam);
    }
}

void AlembicRenderer::loadShader(string path){
    shader.load(path);
    reflectionCount = 4;
    reflection.load("shaders/reflection");
}

void AlembicRenderer::setStage(float stage){
    shader.begin();
    shader.setUniform1f("stage", stage);
    shader.end();
}

void AlembicRenderer::setCamera(ofCamera cam){
    this->cam = cam;
}

void AlembicRenderer::setTime(float t){
    float time = ofMap(t, 0, 1, reader.getMinTime(), reader.getMaxTime(), true);
    reader.setTime(time);
    shader.begin();
    shader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    shader.end();
}

void AlembicRenderer::update(){
    reader.get(cameras[cameraIndex], cam);
//    cam.setPosition(glm::mix(cam.getPosition(), targetCam.getPosition(), 0.9f));
//    cam.setOrientation(glm::mix(cam.getOrientationQuat(), targetCam.getOrientationQuat(), 0.9f));
//    cam.setFov(targetCam.getFov());
//    cam.setScale(targetCam.getScale());
}

void AlembicRenderer::drawCubeMap(){
    ofEnableAlphaBlending();
    for( int i = 0; i < 6; i++ )
    {
        cubeMap.beginDrawingInto3D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i );
        ofClear(0,0,0);
        drawBackground();
        cubeMap.endDrawingInto3D();
    }
    ofDisableAlphaBlending();
}

void AlembicRenderer::drawBackground(){
    
    gradientFBO.begin();
    ofClear(0, 0, 0, 0);
    ofSetColor(255, 0, 255);
    gradient.drawDebug(0, 0, gradientFBO.getWidth(), gradientFBO.getHeight());
    gradientFBO.end();
    
    
    gradientFBO.getTexture().bind();
    sphere.draw();
    gradientFBO.getTexture().unbind();
}

void AlembicRenderer::draw(){
 
    
    mAbcFbo.begin();
    ofClear(0, 0, 0, 0);
    cam.begin(viewport);
    drawScene();
    cam.end();
    mAbcFbo.end();

}


void AlembicRenderer::drawScene(){
    ofEnableDepthTest();
    shader.begin();
    reader.draw();
    shader.end();
    ofDisableDepthTest();
}

void AlembicRenderer::setBaseColor(ofFloatColor color){
    shader.begin();
    shader.setUniform4f("baseColor", color);
    shader.end();
}

void AlembicRenderer::drawReflected(){
    cubeMap.bind();
    reflections.drawMeshGlass(cam, ofVec3f(0, 0, 0));
    cubeMap.unbind();
}
