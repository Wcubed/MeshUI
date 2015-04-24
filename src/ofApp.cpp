#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(width, height);
    ofSetWindowTitle("MeshUI");
    ofSetFrameRate(60);

    // Call every setup
    frame.setup(0, 0);
    genMesh.setup(width, height);
    sphereMesh.setup(width, height);

    // Add buttons
    frame.addButton("Quit", &quitButtonFunction);
}

//--------------------------------------------------------------
void ofApp::update(){
    double dt = ofGetLastFrameTime();

    frame.update(dt);
    genMesh.update(dt);
    sphereMesh.update(dt);
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
    frame.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    frame.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    frame.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    frame.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    frame.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    genMesh.resizeEvent(w, h);
    sphereMesh.resizeEvent(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

// ---- Button functions ---------------------------------------
void ofApp::quitButtonFunction() {
    std::exit(0);
}
