#pragma once


#include "ofMain.h"


typedef void (*functionPointer)();


// Button states
const int BUTTON_STATE_NONEXISTENT = -1;
const int BUTTON_STATE_DISABLED = 0;
const int BUTTON_STATE_IDLE = 1;
const int BUTTON_STATE_HOVER = 2;
const int BUTTON_STATE_PRESSED = 3;
const int BUTTON_STATE_CLICKED = 4;

class Frame;

class Button
{
    friend class Frame;

    public:
        Button();
        Button(std::string _text, functionPointer _func, ofTrueTypeFont* _font);
        virtual ~Button();

        void update(int mouseX, int mouseY, bool* mouseButtons);
        void draw();

        void calcMinSize();
        void reconfigure();

        int getState() { return state; };

        void setFunction(functionPointer _func) { func = _func; };

        // ---------- Parameters ----------
        std::string text;

        int marginX = 10;
        int marginY = 10;

        int paddingX = 10;
        int paddingY = 5;

    protected:

    private:
        // ---------- Parameters ----------
        ofColor disabledColor = ofColor(0, 0, 0, 100);
        ofColor idleColor = ofColor(0, 0, 0, 100);
        ofColor hoverColor = ofColor(0, 255, 255);
        ofColor pressedColor = ofColor(255, 128, 0);

        // ---------- Display variables ----------
        int textX;
        int textY;

        int displayX;
        int displayY;

        int displayWidth;
        int displayHeight;

        int minWidth;
        int minHeight;

        // ---------- Variables ----------
        int state = BUTTON_STATE_IDLE;

        // ---------- Objects----------
        functionPointer func;
        ofTrueTypeFont font;
};
