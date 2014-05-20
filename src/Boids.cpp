//
//  Boids.cpp
//  boidScketch
//
//  Created by hisahayashi on 2014/05/19.
//
//

#include "Boids.h"


//--------------------------------------------------------------
Boids::Boids(){
}

//--------------------------------------------------------------
void Boids::setup( bool _debugMode, int _sw, int _sh ){
    debugMode = _debugMode;
    sw = _sw;
    sh = _sh;
    
    // initialize
    for (int i = 0; i < BOID_COUNT; i++) {
        float x = ofRandom( 0, sw );
        float y = ofRandom( 0, sh );
        float z = 0;
        float ax = ofRandom( -3.0f, 3.0f );
        float ay = ofRandom( -3.0f, 3.0f );
        float az = 0;
        move[i].set( x, y, z );
        verts[i].set( x, y, z );
        accell[i].set( ax, ay, az );
    }
    vbo.setVertexData( verts, BOID_COUNT, GL_DYNAMIC_DRAW);
    distance.resize( BOID_COUNT * BOID_COUNT );
}

//--------------------------------------------------------------
void Boids::update( int _sw, int _sh ){
    sw = _sw;
    sh = _sh;
    
    if( ofGetFrameNum() % 5 == 0 ){
    }
    
    updateDistance();
    updateBoids();
    moveBoids();
}

//--------------------------------------------------------------
void Boids::draw(){
    drawBoids();
}

//--------------------------------------------------------------
void Boids::updateDistance(){
    
    int count = 0;
    
    for ( int i = 0; i < BOID_COUNT; i++){
        ofVec2f posA = verts[i];
        
        //ofLog() << "posA:" << posA;
        
        for (int j = i + 1; j < BOID_COUNT; j++){
            ofVec2f posB = verts[j];
            
            //ofLog() << "posB:" << posB;
            
            float d = ofDist( posA.x, posA.y, posB.x, posB.y );
            int a = i + j * BOID_COUNT;
            int b = i * BOID_COUNT + j;
            distance[ a ] = d;
            distance[ b ] = d;
            
            count++;
        }
    }
    
    //ofLog() << "dist count: " << count;
}

//--------------------------------------------------------------
void Boids::updateBoids(){
    
    int count = 0;
    
    for( int i = 0; i < BOID_COUNT; i++ ){
        
        //近いものから逃げ、遠いものに近寄る、ほどほどのものと並走する
        ofVec3f &v1 = verts[i];
        ofVec3f &a1 = accell[i];
        int b = i * BOID_COUNT;
        float acp_x = 0;  //逃げる加速度
        float acp_y = 0;
        float atp_x = 0;  //近づく加速度
        float atp_y = 0;
        float vp_x = 0;  //並走方向
        float vp_y = 0;
        float ac = 0;  //後で平均値を取る為のカウンター:逃げる
        float at = 0;  //後で平均値を取る為のカウンター:近づく
        float vc = 0;  //後で平均値を取る為のカウンター:並走
        
        for ( int j = 0; j < BOID_COUNT; j++ ){
            if( i != j ){
                
                ofVec3f &v2 = verts[j];
                ofVec3f &a2 = accell[j];
                float dx;
                float dy;
                float d;
                float dis = distance[b + j];
                
                //ofLog() << "dis : " << dis << ", b + j : " << (b + j);
                
                //超近すぎ
                if( dis < vnear ){
                    float r = ofRandom( PI * 2.0 );
                    a1.x = cos(r) * 10;
                    a1.y = sin(r) * 10;
                }
                //近すぎ
                else if( dis < near ){
                    dx = v1.x - v2.x;
                    dy = v1.y - v2.y;
                    acp_x += dx / dis;
                    acp_y += dy / dis;
                    ac++;
                }
                //近すぎず、遠すぎず、ほどほど
                else if( dis < middle ){
                    d = a2.length();
                    vp_x += a2.x / d;
                    vp_y += a2.y / d;
                    
                    if( i == 0 ){
                        //ofLog() << "x: " << boids[j].x << ", y: " << boids[j].y << ", length: " << d ;
                        //ofLog() << "vp_x: " << vp_x << ", vp_y: " << vp_y ;
                    }
                    vc++;
                }
                //遠い
                else if( dis < far ){
                    dx = v1.x - v2.x;
                    dy = v1.y - v2.y;
                    atp_x += dx / dis;
                    atp_y += dy / dis;
                    at++;
                }
                //距離が一定以上のものは遠すぎと判断し、なにもしない
                
                count++;
            }
        }
        
        if( ac ){
            a1.x += acp_x / ac;
            a1.y += acp_y / ac;
        }
        if( at ){
            a1.x -= atp_x / at;
            a1.y -= atp_y / at;
        }
        if( vc ){
            a1.x += vp_x / vc;
            a1.y += vp_y / vc;
        }
        
        if( a1.length() > 10 ){
            a1 = a1.normalize();
        }
        
        v1.x += a1.x;
        v1.y += a1.y;
        
        /*
        if( v1.x < 0 ) v1.x = sw;
        if( v1.x > sw ) v1.x = 0;
        if( v1.y < 0 ) v1.y = sh;
        if( v1.y > sh ) v1.y = 0;
        */
        
        // 壁に反射する
        if( v1.x < 0 ){
            v1.x = 0;
            a1.x = -a1.x;
        }
        if( v1.x > sw ){
            v1.x = sw;
            a1.x = -a1.x;
        }
        if( v1.y < 0 ){
            v1.y = 0;
            a1.y = -a1.y;
        }
        if( v1.y > sh ){
            v1.y = sh;
            a1.y = -a1.y;
        }
    }
    
    //ofLog() << "boid count: " << count;
    
    //vbo.updateVertexData( verts, BOID_COUNT );
}

//--------------------------------------------------------------
void Boids::moveBoids(){
    for( int i = 0; i < BOID_COUNT; i++ ){
        move[i].x += ( verts[i].x - move[i].x ) * 0.3;
        move[i].y += ( verts[i].y - move[i].y ) * 0.3;
    }
    //vbo.updateVertexData( move, BOID_COUNT );
}

void Boids::drawBoids(){
    
    ofSetColor( 255, 255, 255, 255 );
    
    
    //ofNoFill();
    for( int i = 0; i < BOID_COUNT; i++ ){
        ofCircle( move[i].x, move[i].y, 4 );
    }
    
    /*
    //ofPushMatrix();
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //cam.begin();
    
    glPointSize( 1 );
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    vbo.draw( GL_POINTS, 0, BOID_COUNT );
    
    //cam.end();
    //ofPopMatrix();
     */
}

void Boids::setParameter( float _vnear, float _near, float _middle, float _far ){
    vnear = _vnear;
    near = _near;
    middle = _middle;
    far = _far;
}