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
    void setTime(float t);
    void update();
    void drawScene();
    void draw();
    void setStage(float stage);
    void setScale(float scale);
    void setT(float t);
    ofShader shader;
    float reflectionCount;
    bool bLoop;
    ofxAlembic::Reader reader;
    bool bCullFace;
    int face;
    int cameraIndex;
    vector<string>      cameras;
    ofCamera cam;
    ofFbo mAbcFbo;
    ofRectangle viewport;
    ofVec3f pos;

};
#endif /* AlembicRenderer_hpp */
