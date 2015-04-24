#include "Button.h"

Button::Button()
{
    //ctor
}

Button::Button(std::string _text, functionPointer _func, ofTrueTypeFont* _font)
{
    text = _text;
    func = _func;
    font = *_font;
}

Button::~Button()
{
    //dtor
}

void Button::calcMinSize()
{
    minWidth = 2*paddingX + font.stringWidth(text);
    minHeight = 2*paddingY + font.getSize();
}

void Button::reconfigure()
{
    textX = displayX + paddingX;
    textY = displayY + displayHeight/2 + font.getSize()/2;
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

    switch (state) {
    case BUTTON_STATE_DISABLED:
        backgroundColor = disabledColor;
        break;
    case BUTTON_STATE_IDLE:
        backgroundColor = idleColor;
        break;
    case BUTTON_STATE_HOVER:
        backgroundColor = hoverColor;
        break;
    case BUTTON_STATE_PRESSED:
    case BUTTON_STATE_CLICKED:
        backgroundColor = pressedColor;
        break;
    }
    ofSetColor(backgroundColor);
    ofRect(displayX, displayY, displayWidth, displayHeight);
    ofSetColor(0);
    font.drawString(text, textX, textY);
}

