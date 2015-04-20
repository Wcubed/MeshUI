#pragma once

#include "ofMain.h"

class SphereMesh
{
    public:
        SphereMesh();
        virtual ~SphereMesh();

        void setup(int w, int h);
        void update(double dt);
        void draw();

        void resizeEvent(int w, int h);

    protected:
    private:

        // ---------- Parameters ----------
        ofColor color = ofColor(0, 255, 255);

        int X = 158;
        int Z = 256;

        // Line offset
        int L = 10;

        // ---------- Vertices ----------
        GLfloat solidVdata[12][3] = {
        {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
        {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
        {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} };

        GLfloat line1Vdata[12][3] = {
        {-X-1, 0.0, Z+1}, {X+1, 0.0, Z+1}, {-X-1, 0.0, -Z-1}, {X+1, 0.0, -Z-1},
        {0.0, Z+1, X+1}, {0.0, Z+1, -X-1}, {0.0, -Z-1, X+1}, {0.0, -Z-1, -X-1},
        {Z+1, X+1, 0.0}, {-Z-1, X+1, 0.0}, {Z+1, -X-1, 0.0}, {-Z-1, -X-1, 0.0} };

        GLfloat line2Vdata[12][3] = {
        {-X-L, 0.0, Z+L}, {X+L, 0.0, Z+L}, {-X-L, 0.0, -Z-L}, {X+L, 0.0, -Z-L},
        {0.0, Z+L, X+L}, {0.0, Z+L, -X-L}, {0.0, -Z-L, X+L}, {0.0, -Z-L, -X-L},
        {Z+L, X+L, 0.0}, {-Z-L, X+L, 0.0}, {Z+L, -X-L, 0.0}, {-Z-L, -X-L, 0.0} };

        GLint solidIndices[20][3] = {
        {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8},
        {4,8,1}, {8,10,1}, {8,3,10}, {5,3,8},
        {5,2,3}, {2,7,3}, {7,10,3}, {7,6,10},
        {7,11,6}, {11,0,6}, {0,1,6}, {6,1,10},
        {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

        GLint lineIndices[34][2] = {
        {0,1}, {0,4}, {0,6}, {0,9}, {0,11},
        {1,4}, {1,6}, {1,8}, {1,10},
        {2,3}, {2,5}, {2,7}, {2,9}, {2,11},
        {3,5}, {3,8}, {3,7}, {3,10},
        {4,5}, {4,8}, {4,9},
        {5,8}, {5,9},
        {6,7}, {6,10}, {6,11},
        {7,10}, {7,11},
        {8,10},
        {9,11} };

        // ---------- Variables ----------
        int width;
        int height;

        // ---------- Objects ----------
        ofMesh solidMesh;
        ofMesh line1Mesh;
        ofMesh line2Mesh;
};
