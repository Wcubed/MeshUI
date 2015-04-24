#pragma once

#include <vector>

#include "ofMain.h"

#include "Button.h"


class Frame
{
    public:
        Frame();
        virtual ~Frame();

        void setup(int x, int y);
        void update(double dt);
        void draw();

        void reconfigure();

        void setPosition(int x, int y);

        void addButton(std::string text, functionPointer func, int startState=BUTTON_STATE_IDLE);

        // Events
        void mouseMoved(int x, int y);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
    protected:
    private:
        // ---------- Parameters ----------

        // Font size
        int fontSize = 12;

        // Colors
        ofColor backgroundColor = ofColor(0, 0, 0, 100);
        ofColor borderColor = ofColor(0, 150, 255);

        // Position
        int posX;
        int posY;

        // Margin
        int marginX = 15;
        int marginY = 15;

        // Padding
        int paddingX = 0;
        int paddingY = 0;

        // ---------- Display variables ----------
        int displayX;
        int displayY;

        int displayWidth;
        int displayHeight;

        // ---------- Variables ----------

        // Mouse variables
        int mouseX;
        int mouseY;

        bool mouseButtons[3] = {false, false, false};

        // ---------- Objects ----------
        ofTrueTypeFont font;

        // Buttons
        std::vector<Button> buttons;
};
