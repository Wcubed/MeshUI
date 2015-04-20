#include "SphereMesh.h"

// -------------------- Constructor --------------------

SphereMesh::SphereMesh()
{
    //ctor
}

// -------------------- Destructor --------------------

SphereMesh::~SphereMesh()
{
    //dtor
}

// -------------------- Setup --------------------

void SphereMesh::setup(int w, int h) {
    width = w;
    height = h;

    // Set colors
    ofColor solidColor(0);

    ofColor fade1Color = color;
    fade1Color.setBrightness(128);

    // ---------- SolidMesh ----------

    // Set mesh mode
    solidMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    solidMesh.enableColors();
    solidMesh.enableIndices();

    // Add vertices
    for (int i = 0; i < 12; i++) {
        solidMesh.addVertex(ofVec3f(solidVdata[i][0], solidVdata[i][1], solidVdata[i][2]));
        solidMesh.addColor(solidColor);
    }

    // Connect vertices
    for (int i = 0; i < 20; i++) {
        solidMesh.addIndex(solidIndices[i][0]);
        solidMesh.addIndex(solidIndices[i][1]);
        solidMesh.addIndex(solidIndices[i][2]);
    }

    // ---------- Line1Mesh ----------

    // Set mesh mode
    line1Mesh.setMode(OF_PRIMITIVE_LINES);
    line1Mesh.enableColors();
    line1Mesh.enableIndices();

    // Add vertices
    for (int i = 0; i < 12; i++) {
        line1Mesh.addVertex(ofVec3f(line1Vdata[i][0], line1Vdata[i][1], line1Vdata[i][2]));
        line1Mesh.addColor(color);
    }

    // Connect vertices
    for (int i = 0; i < 34; i++) {
        line1Mesh.addIndex(lineIndices[i][0]);
        line1Mesh.addIndex(lineIndices[i][1]);
    }

    // ---------- Line2Mesh ----------

    // Set mesh mode
    line2Mesh.setMode(OF_PRIMITIVE_LINES);
    line2Mesh.enableColors();
    line2Mesh.enableIndices();

    // Add vertices
    for (int i = 0; i < 12; i++) {
        line2Mesh.addVertex(ofVec3f(line2Vdata[i][0], line2Vdata[i][1], line2Vdata[i][2]));
        line2Mesh.addColor(fade1Color);
    }

    // Connect vertices
    for (int i = 0; i < 34; i++) {
        line2Mesh.addIndex(lineIndices[i][0]);
        line2Mesh.addIndex(lineIndices[i][1]);
    }
}

// -------------------- Update --------------------

void SphereMesh::update(double dt) {

}

// -------------------- Draw --------------------

void SphereMesh::draw() {
    ofSetColor(color);
    ofEnableAntiAliasing();

    // Draw the mesh
    solidMesh.draw();
    line1Mesh.draw();
    line2Mesh.draw();
}

// -------------------- ResizeEvent --------------------

void SphereMesh::resizeEvent(int w, int h) {
    width = w;
    height = h;
}
