#pragma once

#include "ofMain.h"

class GenMesh
{
    public:
        GenMesh();
        virtual ~GenMesh();

        void setup(int w, int h);
        void update(double dt);
        void draw();

        void resizeEvent(int w, int h);

    protected:
    private:
        // ---------- Parameters ----------
        ofColor color = ofColor(255);

        float intensityThreshold = 150.0;
        float connectDistance = 30;

        // The factor by which the image will be shrunk
        int shrinkFactor = 4;

        int zMin = -100;
        int zMax = 100;

        // ---------- Variables ----------
        int width;
        int height;

        // ---------- Objects ----------
        ofMesh mesh;
        ofImage image;
};
