#include "UI.h"

// -------------------- Constructor --------------------

UI::UI()
{
    //ctor
}

// -------------------- Destructor --------------------

UI::~UI()
{
    //dtor
}

// -------------------- Setup --------------------

void UI::setup(int w, int h) {
    width = w;
    height = h;

    // Load font
    if (!font.loadFont("Ubuntu-R.ttf", 12)) {
        std::cout << "UI:Error: Font not loaded." << std::endl;
        std::exit(1);
    } else {
        std::cout << "UI: Font loaded." << std::endl;
    }


    // Set colors
    ofColor lightColor = color;
    lightColor.setBrightness(128);
    lightColor.a = 200;

    ofColor darkColor = color;
    darkColor.setBrightness(128);
    darkColor.a = 50;

    ofColor black(0, 0, 0, 0);

    // Create vertices
    ofVec3f topLeft(marginX, marginY, 0.0);
    ofVec3f topRight(width - marginX, marginY, 0.0);
    ofVec3f topMiddleLeft(marginX + fadeOutLength, marginY, 0.0);
    ofVec3f topMiddleRight(width - marginX - fadeOutLength, marginY, 0.0);

    ofVec3f middleLeft(marginX, marginY + menuBarHeight/2, 0.0);
    ofVec3f middleRight(width - marginX, marginY + menuBarHeight/2, 0.0);
    ofVec3f middleMiddleLeft(marginX + fadeOutLength, marginY + menuBarHeight/2, 0.0);
    ofVec3f middleMiddleRight(width - marginX - fadeOutLength, marginY + menuBarHeight/2, 0.0);

    ofVec3f bottomLeft(marginX, marginY + menuBarHeight, 0.0);
    ofVec3f bottomRight(width - marginX, marginY + menuBarHeight, 0.0);
    ofVec3f bottomMiddleLeft(marginX + fadeOutLength, marginY + menuBarHeight, 0.0);
    ofVec3f bottomMiddleRight(width - marginX - fadeOutLength, marginY + menuBarHeight, 0.0);

    // ---------- Menu mesh ----------

    // Set menuMesh mode
    menuMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    menuMesh.enableColors();
    menuMesh.enableIndices();

    // Add vertices
    // 0 - 1 - 2 - 3
    // 4 - 5 - 6 - 7
    // 8 - 9 - 10- 11
    menuMesh.addVertex(topLeft);
    menuMesh.addColor(black);
    menuMesh.addVertex(topMiddleLeft);
    menuMesh.addColor(lightColor);
    menuMesh.addVertex(topMiddleRight);
    menuMesh.addColor(lightColor);
    menuMesh.addVertex(topRight);
    menuMesh.addColor(black);

    menuMesh.addVertex(middleLeft);
    menuMesh.addColor(black);
    menuMesh.addVertex(middleMiddleLeft);
    menuMesh.addColor(darkColor);
    menuMesh.addVertex(middleMiddleRight);
    menuMesh.addColor(darkColor);
    menuMesh.addVertex(middleRight);
    menuMesh.addColor(black);

    menuMesh.addVertex(bottomLeft);
    menuMesh.addColor(black);
    menuMesh.addVertex(bottomMiddleLeft);
    menuMesh.addColor(lightColor);
    menuMesh.addVertex(bottomMiddleRight);
    menuMesh.addColor(lightColor);
    menuMesh.addVertex(bottomRight);
    menuMesh.addColor(black);

    // Connect to make triangles
    menuMesh.addIndex(0);
    menuMesh.addIndex(4);
    menuMesh.addIndex(1);
    menuMesh.addIndex(5);
    menuMesh.addIndex(2);
    menuMesh.addIndex(6);
    menuMesh.addIndex(3);
    menuMesh.addIndex(7);

    menuMesh.addIndex(11);
    menuMesh.addIndex(6);
    menuMesh.addIndex(10);
    menuMesh.addIndex(5);
    menuMesh.addIndex(9);
    menuMesh.addIndex(4);
    menuMesh.addIndex(8);

    // ----------Line mesh ----------

    // Set lineMesh mode
    lineMesh.setMode(OF_PRIMITIVE_LINES);
    lineMesh.enableColors();
    lineMesh.enableIndices();

    // Add vertices
    // 0 - 1 - 2 - 3
    // 4 - 5 - 6 - 7
    lineMesh.addVertex(topLeft);
    lineMesh.addColor(black);
    lineMesh.addVertex(topMiddleLeft);
    lineMesh.addColor(color);
    lineMesh.addVertex(topMiddleRight);
    lineMesh.addColor(color);
    lineMesh.addVertex(topRight);
    lineMesh.addColor(black);

    lineMesh.addVertex(bottomLeft);
    lineMesh.addColor(black);
    lineMesh.addVertex(bottomMiddleLeft);
    lineMesh.addColor(color);
    lineMesh.addVertex(bottomMiddleRight);
    lineMesh.addColor(color);
    lineMesh.addVertex(bottomRight);
    lineMesh.addColor(black);

    // Connect to make lines
    lineMesh.addIndex(0);
    lineMesh.addIndex(1);
    lineMesh.addIndex(1);
    lineMesh.addIndex(2);
    lineMesh.addIndex(2);
    lineMesh.addIndex(3);

    lineMesh.addIndex(4);
    lineMesh.addIndex(5);
    lineMesh.addIndex(5);
    lineMesh.addIndex(6);
    lineMesh.addIndex(6);
    lineMesh.addIndex(7);

    // Reconfigure menu
    reconfigure();
}

// -------------------- Update --------------------

void UI::update(double dt) {
    for (int i = 0; i < buttons.size(); i++) {
        Button* b = &buttons[i];

        if (b->state != BUTTON_STATE_DISABLED) {
            if (mouseX >= b->x and mouseX <= b->x + b->width and mouseY >= b->y and mouseY <= b->y + b->height) {
                if (mouseButtons[0]) {
                    b->state = BUTTON_STATE_PRESSED;
                } else if (b->state == BUTTON_STATE_PRESSED) {
                    b->state = BUTTON_STATE_CLICKED;
                } else {
                    b->state = BUTTON_STATE_HOVER;
                }
            } else {
                b->state = BUTTON_STATE_IDLE;
            }
        }
    }
}

// -------------------- Draw --------------------

void UI::draw() {
    ofSetColor(color);
    ofDisableAntiAliasing();

    // Draw background
    menuMesh.draw();
    lineMesh.draw();

    // Draw buttons
    ofEnableAntiAliasing();

    for (const auto& b : buttons) {
        ofColor backgroundColor;
        ofColor textColor;

        switch (b.state) {
        case BUTTON_STATE_DISABLED:
            backgroundColor = ofColor(0, 0, 0, 0);
            textColor = ofColor(0, 0, 0, 100);
            break;
        case BUTTON_STATE_IDLE:
            backgroundColor = ofColor(0, 0, 0, 0);
            textColor = ofColor(color);
            break;
        case BUTTON_STATE_HOVER:
            backgroundColor = ofColor(color);
            textColor = ofColor(0);
            break;
        case BUTTON_STATE_PRESSED:
        case BUTTON_STATE_CLICKED:
            backgroundColor = ofColor(secColor);
            textColor = ofColor(0);
            break;
        }

        ofSetColor(backgroundColor);
        ofRect(b.x, b.y, b.width, b.height);

        ofSetColor(textColor);
        font.drawString(b.text, b.textX, b.textY);
    }
}

// -------------------- Reconfigure --------------------

void UI::reconfigure() {
    // 0 - 1 - 2 - 3
    // 4 - 5 - 6 - 7
    // 8 - 9 - 10- 11

    menuMesh.setVertex(2, ofVec3f(width - marginX - fadeOutLength, marginY, 0.0));
    menuMesh.setVertex(3, ofVec3f(width - marginX, marginY, 0.0));
    menuMesh.setVertex(6, ofVec3f(width - marginX - fadeOutLength, marginY + menuBarHeight/2, 0.0));
    menuMesh.setVertex(7, ofVec3f(width - marginX, marginY + menuBarHeight/2, 0.0));
    menuMesh.setVertex(10, ofVec3f(width - marginX - fadeOutLength, marginY + menuBarHeight, 0.0));
    menuMesh.setVertex(11, ofVec3f(width - marginX, marginY + menuBarHeight, 0.0));

    // 0 - 1 - 2 - 3
    // 4 - 5 - 6 - 7
    lineMesh.setVertex(2, ofVec3f(width - marginX - fadeOutLength, marginY, 0.0));
    lineMesh.setVertex(3, ofVec3f(width - marginX, marginY, 0.0));
    lineMesh.setVertex(6, ofVec3f(width - marginX - fadeOutLength, marginY + menuBarHeight, 0.0));
    lineMesh.setVertex(7, ofVec3f(width - marginX, marginY + menuBarHeight, 0.0));

    int x = marginX + 2*fadeOutLength/3 + buttonMarginX;

    for (int i = 0; i < buttons.size(); i++) {
        Button* b = &buttons[i];

        int textWidth = font.stringWidth(b->text);
        int textHeight = font.stringHeight(b->text);

        int y = marginY;

        int textX = x + buttonMarginX;
        int textY = marginY + menuBarHeight/2.5 + textHeight/2;

        int buttonWidth = textWidth + 2*buttonMarginX;

        b->x = x;
        b->y = y;
        b->textX = textX;
        b->textY = textY;
        b->width = buttonWidth;
        b->height = menuBarHeight-1; // The -1 is to account for the line at the bottom of the menu

        x += textWidth + 3*buttonMarginX;
    }
}

// -------------------- Add button --------------------

void UI::addButton(std::string text, int startState) {
    Button b;
    b.text = text;

    b.state = startState;

    buttons.push_back(b);

    reconfigure();
}

// -------------------- Get state --------------------

int UI::getButtonState(int id) {
    if (id > buttons.size()) {
        return BUTTON_STATE_NONEXISTENT;
    } else {
        return buttons[id].state;
    }
}

// -------------------- Resize event --------------------

void UI::resizeEvent(int w, int h) {
    width = w;
    height = h;

    reconfigure();
}

void UI::mouseMoved(int x, int y) {
    mouseX = x;
    mouseY = y;
}

void UI::mousePressed(int x, int y, int button) {
    mouseX = x;
    mouseY = y;
    mouseButtons[button] = true;
}

void UI::mouseReleased(int x, int y, int button) {
    mouseX = x;
    mouseY = y;
    mouseButtons[button] = false;
}
