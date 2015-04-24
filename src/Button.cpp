#include "Button.h"

Button::Button()
{
    //ctor
}

Button::Button(std::string _text, functionPointer _func, ofTrueTypeFont* _font, int startState)
{
    text = _text;
    func = _func;
    font = *_font;
    state = startState;
}

Button::~Button()
{
    //dtor
}

void Button::calcMinSize()
{
    minWidth = 2*paddingX + font.stringWidth(text) + 3;
    minHeight = 2*paddingY + font.getSize();
}

void Button::reconfigure(int x, int y, int width, int height)
{
    displayX = x;
    displayY = y;
    displayWidth = width;
    displayHeight = height;

    textX = displayX + paddingX;
    textY = displayY + displayHeight/2 + font.getSize()/3;
}

void Button::update(int mouseX, int mouseY, bool* mouseButtons)
{
    if (state != BUTTON_STATE_DISABLED)
    { // If active
        if (displayX <= mouseX and mouseX <= displayX + displayWidth and
            displayY <= mouseY and mouseY <= displayY + displayHeight)
        { // Mouse is over button
            if (mouseButtons[0])
            {
                state = BUTTON_STATE_PRESSED;
            } else {
                if (state == BUTTON_STATE_PRESSED) {
                    state = BUTTON_STATE_CLICKED;
                    // Call function
                    if (func != nullptr) {
                        func();
                    }
                } else {
                    state = BUTTON_STATE_HOVER;
                }
            }
        } else { // Mouse is not over button
            state = BUTTON_STATE_IDLE;
        }
    }
}

void Button::draw()
{
    ofColor backgroundColor;
    ofColor textColor;

    switch (state) {
    case BUTTON_STATE_DISABLED:
        backgroundColor = disabledColor;
        textColor = ofColor(100);
        break;
    case BUTTON_STATE_IDLE:
        backgroundColor = idleColor;
        textColor = ofColor(255);
        break;
    case BUTTON_STATE_HOVER:
        backgroundColor = hoverColor;
        textColor = ofColor(255);
        break;
    case BUTTON_STATE_PRESSED:
    case BUTTON_STATE_CLICKED:
        backgroundColor = pressedColor;
        textColor = ofColor(255);
        break;
    }

    ofDisableAntiAliasing();

    // Background
    ofSetColor(backgroundColor);
    ofRect(displayX + colorBorder + 1, displayY + colorBorder, displayWidth - (colorBorder + 4), displayHeight - (colorBorder + 3));

    // Borders
    ofSetColor(borderColor);
    ofLine(displayX, displayY, displayX + displayWidth, displayY); // Top
    ofLine(displayX, displayY + displayHeight, displayX + displayWidth, displayY + displayHeight); // Bottom
    ofLine(displayX + 1, displayY, displayX + 1, displayY + displayHeight); // Left
    ofLine(displayX + displayWidth, displayY, displayX + displayWidth, displayY + displayHeight); // Right

    // Text
    ofEnableAntiAliasing();
    ofSetColor(textColor);
    font.drawString(text, textX, textY);
}

