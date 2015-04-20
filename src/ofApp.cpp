#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(width, height);
    ofSetWindowTitle("MeshUI");
    ofSetFrameRate(60);

    // Call every setup
    ui.setup(width, height);
    genMesh.setup(width, height);
    sphereMesh.setup(width, height);

    // Add buttons
    ui.addButton("Sphere");
    ui.addButton("Image");
    ui.addButton("Quit");
    ui.addButton("Button with a long name that does nothing");
}

//--------------------------------------------------------------
void ofApp::update(){
    double dt = ofGetLastFrameTime();

    ui.update(dt);
    genMesh.update(dt);
    sphereMesh.update(dt);

    if (ui.getButtonState(0) == BUTTON_STATE_CLICKED) {
        state = 0;
        easyCam.reset();
    } else if (ui.getButtonState(1) == BUTTON_STATE_CLICKED) {
        state = 1;
        easyCam.reset();
    } else if (ui.getButtonState(2) == BUTTON_STATE_CLICKED) {
        std::exit(0);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Clear screen
    ofColor centerColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

    ofEnableDepthTest();

    // Use the camera
    easyCam.begin();
        ofPushMatrix();
            if (state == 0) {
                sphereMesh.draw();
            } else if (state == 1) {
                // Place the camera to view the middle of the screen
                ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
                // Draw content
                genMesh.draw();
            }
        ofPopMatrix();
    easyCam.end();

    ofDisableDepthTest();

    // Draw ui
    ui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ui.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ui.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ui.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ui.resizeEvent(w, h);
    genMesh.resizeEvent(w, h);
    sphereMesh.resizeEvent(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
