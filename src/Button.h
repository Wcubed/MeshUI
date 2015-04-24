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

class Button
{
    public:
        Button();
        Button(std::string _text, functionPointer _func, ofTrueTypeFont* _font, int startState);
        virtual ~Button();

        void update(int mouseX, int mouseY, bool* mouseButtons);
        void draw();

        void calcMinSize();
        void reconfigure(int x, int y, int width, int height);

        int getState() { return state; };

        int getMinWidth() { return minWidth; };
        int getMinHeight() { return minHeight; };

        int getDisplayWidth() { return displayWidth; };
        int getDisplayHeight() { return displayHeight; };

        void setFunction(functionPointer _func) { func = _func; };

        // ---------- Parameters ----------
        std::string text;

        int marginX = 10;
        int marginY = 10;

        int paddingX = 12;
        int paddingY = 7;

    protected:

    private:
        // ---------- Parameters ----------
        ofColor disabledColor = ofColor(0, 0, 0, 100);
        ofColor idleColor = ofColor(0, 0, 0, 100);
        ofColor hoverColor = ofColor(0, 150, 255, 200);
        ofColor pressedColor = ofColor(255, 128, 0, 200);

        ofColor borderColor = ofColor(0, 200, 200);

        int colorBorder = 2;

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
        int state;

        // ---------- Objects----------
        functionPointer func;
        ofTrueTypeFont font;
};
