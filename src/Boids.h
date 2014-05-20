//
//  Boids.h
//  boidScketch
//
//  Created by hisahayashi on 2014/05/19.
//
//

#ifndef __boidScketch__Boids__
#define __boidScketch__Boids__
#define BOID_COUNT 1000

#include "ofMain.h"

class Boids : public ofBaseApp{
    
public:
    Boids();
    void setup( bool _debugMode, int _sw, int _sh );
    void update( int _sw, int _sh );
    void updateDistance();
    void updateBoids();
    void moveBoids();
    void draw();
    void drawBoids();
    void setParameter( float _vnear, float _near, float _middle, float _far );
    
    int sw, sh;
    bool debugMode;
    
    ofVbo vbo;
    ofVec3f verts[BOID_COUNT];
    ofVec3f move[BOID_COUNT];
    ofVec3f accell[BOID_COUNT];
    
    vector <float> distance;
    
    float vnear;
    float near;
    float middle;
    float far;
    
};

#endif /* defined(__boidScketch__Boids__) */

