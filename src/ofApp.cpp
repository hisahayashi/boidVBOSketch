#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // debugMode
    debugMode = true;
    
    // panel
    ofxGuiSetFont( "VeraMono.ttf", 8, true, true );
    ofxGuiSetTextPadding( 4 );
    ofxGuiSetDefaultWidth( 200 );
    ofxGuiSetDefaultHeight( 18 );
    gui.setup("panel");
    
    gui.add( fps.set( "fps" ));
    gui.add( vnear.set( "vnear", 1, vnearMin, vnearMax ));
    gui.add( near.set( "near", 2, nearMin, nearMax ));
    gui.add( middle.set( "middle", 22, middleMin, middleMax ));
    gui.add( far.set( "far", 24, farMin, farMax ));
    
    // scene setup
    ofSetVerticalSync(true);
    ofSetFrameRate( 60 );
    ofBackground( ofColor( 0, 0, 0 ) );
    ofSetBackgroundAuto( false );
    ofSetCircleResolution( 8 );
    resize();
    
    // screen setup
    //ofSetWindowPosition( 0, 0 );
    //ofSetWindowShape( ofGetScreenWidth(), ofGetScreenHeight() );
    ofSetWindowShape( 640, 480 );
    
    // nano kontrol
    nk2.setup();
    nk2.hide();
    
    boids.setup( debugMode, sw, sh );
}

//--------------------------------------------------------------
void ofApp::update(){
    resize();
    
    // gui
    fps = ofToString( ofGetFrameRate() );
    
    // boids
    boids.setParameter( vnear, near, middle, far );
    boids.update( sw, sh );
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // stage fill
    ofSetColor( 0, 0, 0, 100 );
    ofRect( 0, 0, sw, sh );
    
    // gui
    gui.draw();
    
    // nano kontrol
    vector <float> sdr;
    vector <ofVec2f> knb;
    vector <float> sBtn;
    
    for( int i = 0; i < nk2.MixerChannels; i++ ){
        sdr.push_back( nk2.channel[i].slider );
        knb.push_back( nk2.channel[i].knobOffset );
        sBtn.push_back( nk2.channel[i].button[i] );
    }
    
    //ofLog() << "nk2.channel: " << nk2.channel;
    //ofLog() << sdr[0] << ", " << sdr[1] << ", " << sdr[2] << ", " << sdr[3];
    
    vnear = sdr[0] * ( vnearMax - vnearMin ) + vnearMin;
    near = sdr[1] * ( nearMax - nearMin ) + nearMin;
    middle = sdr[2] * ( middleMax - middleMin ) + middleMin;
    far = sdr[3] * ( farMax - farMin ) + farMin;
    
    nk2.draw();
    
    // draw boids
    boids.draw();
}

void ofApp::trackNextEvent(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}


//--------------------------------------------------------------
void ofApp::resize(){
    sw = ofGetWindowWidth();
    sh = ofGetWindowHeight();
}