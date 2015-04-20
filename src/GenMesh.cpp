#include "GenMesh.h"

// -------------------- Constructor --------------------

GenMesh::GenMesh()
{
    //ctor
}

// -------------------- Destructor --------------------

GenMesh::~GenMesh()
{
    //dtor
}

// -------------------- Setup --------------------

void GenMesh::setup(int w, int h) {
    width = w;
    height = h;

    // Load image
    image.loadImage("stars.png");
    image.resize(image.getWidth()/shrinkFactor, image.getHeight()/shrinkFactor);

    // Set mesh mode
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    mesh.enableIndices();

    // Get image width and height
    int iw = image.getWidth();
    int ih = image.getHeight();

    // ---------- Generate vertices ----------

    // Loop over every pixel in the image
    for (int x = 0; x < iw; x++) {
        for (int y = 0; y < ih; y++) {

            // Get the color and intensity of the pixel
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();

            // If the intensity is above the threshold
            if (intensity >= intensityThreshold) {
                // Get the saturation of the pixel
                float saturation = c.getSaturation();
                // Map the saturation to the z value
                float z = ofMap(saturation, 0, 255, zMin, zMax);

                // Add a vertex with the pixels position and color
                ofVec3f pos(x * shrinkFactor, y * shrinkFactor, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
            }
        }
    }

    // ---------- Connect vertices ----------

    int numVerts = mesh.getNumVertices();
    int numLines = 0;

    // Check every pair of vertices
    for (int a = 0; a < numVerts; a++) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b < numVerts; b++) {
            ofVec3f vertb = mesh.getVertex(b);

            // Calculate distance
            float distance = verta.distance(vertb);

            // If the distance is below the threshold
            if (distance <= connectDistance) {
                // Connect the vertices
                mesh.addIndex(a);
                mesh.addIndex(b);

                // Add 1 to the line count
                numLines++;
            }
        }
    }

    std::cout << "Generated " << numVerts << " vertices and "
              << numLines << " lines." << std::endl;
}

// -------------------- Update --------------------

void GenMesh::update(double dt) {

}

// -------------------- Draw --------------------

void GenMesh::draw() {
    ofSetColor(color);
    ofEnableAntiAliasing();

    // Draw the mesh
    mesh.draw();
}

// -------------------- ResizeEvent --------------------

void GenMesh::resizeEvent(int w, int h) {
    width = w;
    height = h;
}
