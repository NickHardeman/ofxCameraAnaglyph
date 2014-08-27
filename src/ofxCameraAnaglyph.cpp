//
//  CameraAnaglyph.cpp
//  iTunesVisualizerBullet
//
//  Created by Nick Hardeman on 8/21/14.
//

#include "ofxCameraAnaglyph.h"

//--------------------------------------------------------------
ofxCameraAnaglyph::ofxCameraAnaglyph() {
    enableStereo();
    eyeSeparation = 0.179;
    
    DTOR        = 0.0174532925;
    RTOD        = 57.2957795;
    
    focalLength = 25.f;
    
    
    bHasRunOnce = false;
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::beginLeft() {
    if(!bHasRunOnce) {
        begin(); end();
        bHasRunOnce = true;
    }
    calculateCamSettings( true );
    glColorMask(true, false, false, true);
    loadMatrices( true );
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::endLeft() {
    glColorMask(true, true, true, true);
    ofSetupScreen();
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::beginRight() {
    if(!bHasRunOnce) {
        begin(); end();
        bHasRunOnce = true;
    }
    
    calculateCamSettings( false );
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glColorMask(false, true, true, true);
    
    loadMatrices( false );
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::endRight() {
    glColorMask(true, true, true, true);
    ofSetupScreen();
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::endStereo() {
    glColorMask(true, true, true, true);
    ofSetupScreen();
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::calculateCamSettings( bool bLeft ) {
    
    settings.near = getNearClip();
	if (settings.near < 0.1) settings.near = 0.1;
    settings.far = getFarClip();
    
	// Misc stuff
	settings.ratio      = ofGetCurrentViewport().width / (double)ofGetCurrentViewport().height;
	settings.radians    = DTOR * getFov() / 2;
	settings.wd2        = settings.near * tan( settings.radians );
	settings.ndfl       = settings.near / focalLength;
    
    if( bLeft ) {
        settings.left  = - settings.ratio * settings.wd2 + 0.5 * eyeSeparation * settings.ndfl;
        settings.right =   settings.ratio * settings.wd2 + 0.5 * eyeSeparation * settings.ndfl;
    } else {
        settings.left  = - settings.ratio * settings.wd2 - 0.5 * eyeSeparation * settings.ndfl;
		settings.right =   settings.ratio * settings.wd2 - 0.5 * eyeSeparation * settings.ndfl;
    }
    
    settings.top    = settings.wd2;
    settings.bottom = -settings.wd2;
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::loadMatrices( bool bLeft ) {
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum( settings.left, settings.right, settings.bottom, settings.top, settings.near, settings.far);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    ofVec3f r = getSideDir().getNormalized() * (eyeSeparation/3.f);
    
    if( bLeft ) r *= -1.f;
    
    ofVec3f prevPos = getPosition();
    setPosition( getPosition() + r );
    
    ofSetMatrixMode(OF_MATRIX_MODELVIEW);
    ofLoadMatrix( getModelViewMatrix() );
    
    setPosition( prevPos );
    
}

//--------------------------------------------------------------
bool ofxCameraAnaglyph::isStereo() {
    return bStereo;
}

//--------------------------------------------------------------
bool ofxCameraAnaglyph::isMono() {
    return bStereo;
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::enableStereo() {
    bStereo = true;
}

//--------------------------------------------------------------
void ofxCameraAnaglyph::disableStereo() {
    bStereo = false;
}













