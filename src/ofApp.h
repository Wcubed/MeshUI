#pragma once

#include "ofMain.h"

#include "Frame.h"
#include "GenMesh.h"
#include "SphereMesh.h"


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

		// Button functions
		static void quitButtonFunction();

    private:
        int width = 800;
        int height = 800;

        int state = 0;

        // Camera
        ofEasyCam easyCam;

        Frame frame;
        GenMesh genMesh;
        SphereMesh sphereMesh;
};
