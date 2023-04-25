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

class AlembicRenderer {
public:
    AlembicRenderer();
    ~AlembicRenderer();
    void setup(int width, int height);
    void load(string path);
    void loadShader(string path);
    void setBaseColor(ofFloatColor color);
    void setCamera(ofCamera cam);
    void setTime(float t);
    void update();
    void drawScene();
    void draw();
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
    ofFbo mAbcFbo;
    ofRectangle viewport;
    ofSpherePrimitive sphere;
    ofVec3f pos;
    ofFbo gradientFBO;

};
#endif /* AlembicRenderer_hpp */
