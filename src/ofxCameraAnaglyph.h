//
//  CameraAnaglyph.h
//  iTunesVisualizerBullet
//
//  Created by Nick Hardeman on 8/21/14.
//

// Based on techniques described by Paul Bourke 
// http://paulbourke.net/stereographics/stereorender/

#pragma once
#include "ofMain.h"

class ofxCameraAnaglyph : public ofCamera {
public:
    
    ofxCameraAnaglyph();
    
    void beginLeft();
    void endLeft();
    
    void beginRight();
    void endRight();
    
    void endStereo();
    
    void calculateCamSettings( bool bLeft );
    
    bool isStereo();
    bool isMono();
    void enableStereo();
    void disableStereo();
    
    bool isColorMaskEnabled();
    void enableColorMask();
    void disableColorMask();
    void toggleColorMask();
    
    void setRedEye( bool bLeftEye );
    
    ofParameter<bool> bStereo;
    ofParameter<float> eyeSeparation;
    ofParameter<float> focalLength;
    
    struct AnaglyphSettings {
        GLdouble ratio, radians, wd2, ndfl;
        GLdouble left, right, top, bottom, near, far;
    };
    
protected:
    void loadMatrices( bool bLeft );
    
    AnaglyphSettings settings;
    
    double DTOR;
    double RTOD;
    
    // need to run the camera at least once to calculate all of the settings
    bool bHasRunOnce;
    bool bColorMaskEnabled;
    bool bLeftEyeRed;
};







