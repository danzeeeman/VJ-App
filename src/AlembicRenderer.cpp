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
    mAbcFbo.allocate(width, height, GL_RGBA16);
    viewport = ofRectangle(0, 0, width, height);
    mAbcFbo.begin();
    ofClear(0, 0, 0);
    mAbcFbo.end();
    loadShader(ofToDataPath("shaders/shader"));
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
}

void AlembicRenderer::setStage(float stage){
    shader.begin();
    shader.setUniform1f("stage", stage);
    shader.end();
}

void AlembicRenderer::setTime(float t){
    float time = ofMap(t, 0, 1, reader.getMinTime(), reader.getMaxTime(), true);
    reader.setTime(time);
    shader.begin();
    shader.setUniform1f("elapsedTime", time);
    shader.end();
}

void AlembicRenderer::update(){
    reader.get(cameras[cameraIndex], cam);
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

void AlembicRenderer::setScale(float scale) {
    shader.begin();
    shader.setUniform1f("scale", scale);
    shader.end();
}

void AlembicRenderer::setT(float t) {
    shader.begin();
    shader.setUniform1f("t", t);
    shader.end();
}

void AlembicRenderer::setBaseColor(ofFloatColor color){
    shader.begin();
    shader.setUniform4f("baseColor", color);
    shader.end();
}
