#pragma once

#include <string>
#include <vector>

#include "ofMain.h"


// Button states
const int BUTTON_STATE_NONEXISTENT = -1;
const int BUTTON_STATE_DISABLED = 0;
const int BUTTON_STATE_IDLE = 1;
const int BUTTON_STATE_HOVER = 2;
const int BUTTON_STATE_PRESSED = 3;
const int BUTTON_STATE_CLICKED = 4;


struct Button {
    std::string text;
    int state;

    int x;
    int y;
    int textX;
    int textY;

    int width;
    int height;

    int marginX;
    int marginY;
    int paddingX;
    int paddingY;
};

class UI
{
    public:
        UI();
        virtual ~UI();

        // ----------
        void setup(int w, int h);
        void update(double dt);
        void draw();

        // Button functions
        void reconfigure();

        void addButton(std::string text, int startState=BUTTON_STATE_IDLE);
        int getButtonState(int id);

        // Events
        void resizeEvent(int w, int h);

        void mouseMoved(int x, int y);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);

    protected:
    private:
        // ---------- Parameters ----------
        int marginX = 10;
        int marginY = 10;

        int fontSize = 12;

        ofColor color = ofColor(0, 100, 200);
        ofColor secColor = ofColor(255, 128, 0);

        // ---------- Variables ----------
        int screenWidth;
        int screenHeight;

        int height = 10;

        int mouseX;
        int mouseY;

        bool mouseButtons[3] = {false, false, false};

        // ---------- Objects ----------
        ofTrueTypeFont font;

        std::vector<Button> buttons;
};
