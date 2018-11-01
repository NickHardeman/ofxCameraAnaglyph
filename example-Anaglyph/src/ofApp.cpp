#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 );
    
    cam.setPosition( 0, 0, 10 );
    cam.lookAt( ofVec3f(0,0,0));
    
    boxes.assign( 100, ofBoxPrimitive() );
    
    for( int i = 0; i < boxes.size(); i++ ) {
//        boxes.push_back( ofBoxPrimitive() );
        ofBoxPrimitive& box = boxes[i];
        box.set( ofRandom(0.3, 0.75) );
        box.roll( ofRandom(0, 180));
        box.tilt( ofRandom(0, 180));
        float tx = ofRandom( -7, 7 );
        float ty = ofRandom( -5, 5 );
        float tz = ofRandom( -7, 7 );
        box.setPosition( tx, ty, tz );
        colors.push_back( ofColor( ofRandom(40,55), ofRandom(100, 160), ofRandom(130, 220)));
    }
    
    cam.enableStereo();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.eyeSeparation   = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 1., true );
    cam.focalLength     = ofMap( ofGetMouseY(), 0, ofGetHeight(), 0, 100, true );
    
    cam.orbit( ofGetElapsedTimef() * 3.f, 0.2f, 10 );
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    ofEnableDepthTest();
    if( cam.isStereo() ) {
        cam.beginLeft();
    } else {
        cam.begin();
    }
    
    for( int i = 0; i < boxes.size(); i++ ) {
        ofSetColor( colors[i] );
        boxes[i].draw();
        ofSetColor(30, 30, 30);
        ofLine( ofPoint(0,0,0), boxes[i].getPosition() );
    }
    
    // draw again into the right eye //
    if( cam.isStereo() ) {
        cam.beginRight();
        for( int i = 0; i < boxes.size(); i++ ) {
            ofSetColor( colors[i] );
            boxes[i].draw();
            ofSetColor(30, 30, 30);
            ofLine( ofPoint(0,0,0), boxes[i].getPosition() );
        }
    }
    
    if( cam.isStereo() ) {
        cam.endStereo();
    } else {
        cam.end();
    }
    ofDisableDepthTest();
    
    ofSetColor(30, 30, 30 );
    ofDrawBitmapString("Eye Separation: "+ofToString( cam.eyeSeparation, 3), 40, 40 );
    ofDrawBitmapString("Eye Focal Length: "+ofToString( cam.focalLength, 3), 40, 60 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == ' ' ) {
        if( cam.isStereo() ) cam.disableStereo();
        else cam.enableStereo();
    }
    if( key == 'f' ) {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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