//
//  AlembicRenderer.hpp
//  shapes
//
//  Created by Dan Moore on 2/29/20.
//

#ifndef AlembicRenderer_hpp
#define AlembicRenderer_hpp

#include "ofMain.h"
#include "ofxAlembic.h"
#include "ofxCubeMap.h"
#include "ofxColorGradient.h"
#include "ofxReflectionRefraction.h"

class AlembicRenderer {
public:
    AlembicRenderer();
    ~AlembicRenderer();
    void setup(int width, int height);
    void setBackgroundColors(vector<ofColor> colors);
    void load(string path);
    void loadShader(string path);
    void setBaseColor(ofFloatColor color);
    void setCamera(ofCamera cam);
    void setTime(float t);
    void update();
    void drawScene();
    void drawBackground();
    void draw();
    void drawReflected();
    void drawCubeMap();
    void setStage(float stage);
    ofShader shader;
    float reflectionCount;
    bool bLoop;
    ofxAlembic::Reader reader;
    bool bCullFace;
    int face;
    int cameraIndex;
    vector<string>      cameras;
    ofCamera cam;
    ofCamera targetCam;
    ofShader reflection;
    ofxCubeMap cubeMap;
    ofFbo mAbcFbo;
    ofRectangle viewport;
    ofSpherePrimitive sphere;
    ofVec3f pos;
    ofxColorGradient<ofColor> gradient;
    ofFbo gradientFBO;
    ofxReflectionRefraction reflections;
};
#endif /* AlembicRenderer_hpp */
