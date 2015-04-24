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
    screenWidth = w;
    screenHeight = h;

    // Load font
    if (!font.loadFont("Ubuntu-R.ttf", fontSize)) {
        std::cout << "UI:Error: Font not loaded." << std::endl;
        std::exit(1);
    } else {
        std::cout << "UI: Font loaded." << std::endl;
    }

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
                    if (b->state == BUTTON_STATE_HOVER) {
                        b->state = BUTTON_STATE_PRESSED;
                    }
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
    ofDisableAntiAliasing();

    ofColor buttonColor(54, 0, 140);

    ofColor buttonSecColor(0, 100, 255);

    ofSetColor(0, 0, 0, 100);
    ofFill();

    ofRect(marginX, marginY, screenWidth - marginX*2, height);

    ofSetColor(color);
    ofLine(marginX, marginY, screenWidth - marginX, marginY);
    ofLine(marginX, marginY + height, screenWidth - marginX, marginY + height);
    ofLine(marginX+1, marginY, marginX+1, marginY + height);
    ofLine(screenWidth - marginX, marginY, screenWidth - marginX, marginY + height);

    // Draw buttons
    ofEnableAntiAliasing();

    for (const auto& b : buttons) {
        ofColor backgroundColor;
        ofColor textColor;

        switch (b.state) {
        case BUTTON_STATE_DISABLED:
            backgroundColor = ofColor(0, 0, 0, 200);
            textColor = ofColor(200, 200, 200, 100);
            break;
        case BUTTON_STATE_IDLE:
            backgroundColor = ofColor(0, 0, 0, 200);
            textColor = ofColor(255);
            break;
        case BUTTON_STATE_HOVER:
            backgroundColor = ofColor(buttonColor);
            textColor = ofColor(255);
            break;
        case BUTTON_STATE_PRESSED:
        case BUTTON_STATE_CLICKED:
            backgroundColor = ofColor(buttonSecColor);
            textColor = ofColor(255);
            break;
        }

        ofSetColor(backgroundColor);
        ofRect(b.x, b.y, b.width, b.height);

        ofSetColor(textColor);
        font.drawString(b.text, b.textX, b.textY);

        ofDisableAntiAliasing();

        ofSetColor(color);
        ofLine(b.x, b.y, b.x + b.width, b.y);
        ofLine(b.x, b.y + b.height, b.x + b.width, b.y + b.height);
        ofLine(b.x+1, b.y, b.x+1, b.y + b.height);
        ofLine(b.x + b.width, b.y, b.x + b.width, b.y + b.height);
    }
}

// -------------------- Reconfigure --------------------

void UI::reconfigure() {

    int x = marginX;

    for (int i = 0; i < buttons.size(); i++) {
        Button* b = &buttons[i];

        int textWidth = font.stringWidth(b->text);
        int textHeight = font.stringHeight(b->text);

        x += b->marginX;

        b->x = x;
        b->y = marginY + b->marginY;

        b->width = textWidth + 2*b->paddingX;
        b->height = textHeight + 2*b->paddingY;

        b->textX = b->x + b->paddingX;
        b->textY = b->y + (b->height/2) + (textHeight/2) - 3;

        int totalHeight = b->height + 2*b->marginY;

        if (totalHeight > height) {
            height = totalHeight;
        }

        x += b->width;
    }
}

// -------------------- Add button --------------------

void UI::addButton(std::string text, int startState) {
    Button b;
    b.text = text;

    b.state = startState;

    b.marginX = 10;
    b.marginY = 10;
    b.paddingX = 10;
    b.paddingY = 6;

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
    screenWidth = w;
    screenHeight = h;

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
