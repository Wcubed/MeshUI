#include "Frame.h"

Frame::Frame()
{
    //ctor
}

Frame::~Frame()
{
    //dtor
}

// ---- Setup --------------------

void Frame::setup(int x, int y)
{
    posX = x;
    posY = y;

    // Load font
    if (!font.loadFont("Ubuntu-R.ttf", fontSize)) {
        std::cout << "UI:Error: Font not loaded." << std::endl;
        std::exit(1);
    } else {
        std::cout << "UI: Font loaded." << std::endl;
    }

    reconfigure();
}

// ---- Update --------------------

void Frame::update(double dt)
{

}

// ---- Draw --------------------

void Frame::draw()
{
    ofDisableAntiAliasing();

    // Background
    ofSetColor(backgroundColor);
    ofRect(displayX, displayY, displayWidth, displayHeight);

    // Borders
    ofSetColor(borderColor);
    ofLine(displayX, displayY, displayX + displayWidth, displayY); // Top
    ofLine(displayX, displayY + displayHeight, displayX + displayWidth, displayY + displayHeight); // Bottom
    ofLine(displayX + 1, displayY, displayX + 1, displayY + displayHeight); // Left
    ofLine(displayX + displayWidth, displayY, displayX + displayWidth, displayY + displayHeight); // Right

    // Draw buttons
    for (unsigned int i = 0; i < buttons.size(); i++) {
        buttons[i].draw();
    }
}

// ---- Reconfigure --------------------

void Frame::reconfigure()
{
    // Calculate own position
    displayX = posX + marginX;
    displayY = posY + marginY;

    // Are there buttons in the first place?
    if (buttons.size() > 0) {

        int currentX = displayX;
        int currentY = displayY;

        // Add the largest distance (padding or button margin) to the starting position
        if (buttons[0].marginX > paddingX) {
            currentX += buttons[0].marginX;
        } else {
            currentX += paddingX;
        }

        // Calculate sizes and positions for the buttons
        for (int i = 0; i < buttons.size(); i++) {
            Button* b = &buttons[i];

            b->calcMinSize();

            int buttonWidth = b->getMinWidth();
            int buttonHeight = b->getMinHeight();

            int buttonX = currentX;

            int buttonY;

            if (b->marginY > paddingY) {
                buttonY = currentY + b->marginY;
            } else {
                buttonY = currentY + paddingY;
            }

            b->reconfigure(buttonX, buttonY, buttonWidth, buttonHeight);

            currentX += b->getDisplayWidth();

            // If button is not the last button
            if (i < buttons.size()-1) {
                if (b->marginX > buttons[i+1].marginX) {
                    currentX += b->marginX;
                } else {
                    currentX += buttons[i+1].marginX;
                }
            } else {
                if (b->marginX > paddingX) {
                    displayWidth = currentX + b->marginX - displayX;
                } else {
                    displayWidth = currentX + paddingX - displayX;
                }
            }

            int totalHeight = 0;

            // Get the total height of the button, displayHeight + margin or padding
            if (b->marginY > paddingY) {
                totalHeight = 2*b->marginY + b->getDisplayHeight();
            } else {
                totalHeight = 2*paddingX + b->getDisplayHeight();
            }

            // Figure out the height of the frame
            if (totalHeight > displayHeight) {
                displayHeight = totalHeight;
            }
        }
    } else { // There are no buttons
        displayWidth = 2*paddingX;
        displayHeight = 2*paddingY;
    }
}

void Frame::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}

void Frame::addButton(std::string text, functionPointer func, int startState)
{
    Button b = Button(text, func, &font, startState);

    buttons.push_back(b);

    reconfigure();
}

// ---- Events --------------------

void Frame::mouseMoved(int x, int y)
{
    mouseX = x;
    mouseY = y;

    for (unsigned int i = 0; i < buttons.size(); i++) {
        buttons[i].update(x, y, mouseButtons);
    }
}

void Frame::mousePressed(int x, int y, int button)
{
    mouseX = x;
    mouseY = y;
    mouseButtons[button] = true;

    for (unsigned int i = 0; i < buttons.size(); i++) {
        buttons[i].update(x, y, mouseButtons);
    }
}

void Frame::mouseReleased(int x, int y, int button)
{
    mouseX = x;
    mouseY = y;
    mouseButtons[button] = false;

    for (unsigned int i = 0; i < buttons.size(); i++) {
        buttons[i].update(x, y, mouseButtons);
    }
}

