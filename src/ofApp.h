#pragma once

#include "ofMain.h"
#include "NanoKontrol2.h"
#include "ofxGui.h"
#include "Boids.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int sw, sh;
    bool debugMode;
    
    void resize();
    
    //--------------------------------------
    // gui
    ofxPanel gui;
    ofParameter <string> fps;
    
    //--------------------------------------
    // boids parameters
    Boids boids;
    
    ofParameter <float> vnear;
    const float vnearMin = 0.5;
    const float vnearMax = 20;
    
    ofParameter <float> near;
    const float nearMin = 1;
    const float nearMax = 50;
    
    ofParameter <float> middle;
    const float middleMin = 11;
    const float middleMax = 200;
    
    ofParameter <float> far;
    const float farMin = 12;
    const float farMax = 500;
    
    //--------------------------------------
    // nano kontrol
    MixerChannel mc;
    NanoKontrol2 nk2;
    void trackNextEvent();
};
