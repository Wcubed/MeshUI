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

        int buttonMarginX = 7;

        int menuBarHeight = 25;
        int fadeOutLength = 100;

        int lineWidth = 1;

        ofColor color = ofColor(0, 255, 255, 200);
        ofColor secColor = ofColor(255, 128, 0, 200);

        // ---------- Variables ----------
        int width;
        int height;

        int mouseX;
        int mouseY;

        bool mouseButtons[3] = {false, false, false};

        // ---------- Objects ----------
        ofTrueTypeFont font;

        ofMesh menuMesh;
        ofMesh lineMesh;

        std::vector<Button> buttons;
};
