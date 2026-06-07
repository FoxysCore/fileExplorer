//
// Created by dimon on 06.06.2026.
//

#include "ButtonCodeViewer.h"
#include "../../utils/Terminal.hpp"

ButtonCodeViewer::ButtonCodeViewer(App& app): Drawable(app) {}

std::string ButtonCodeViewer::getPrompt() {
    return "Button Code Viewer";
}

DrawableType ButtonCodeViewer::getType() {
    return BUTTON_CODE_VIEWER;
}

void ButtonCodeViewer::onButton(int btn) {
    if (btn == 32) {
        int selected = this->getApp().getActiveDrawablePosition();
        this->getApp().createDrawable(MENU, selected);
        this->getApp().removeDrawable(selected+1);
    }
    else this->lastCode = btn;
}

void ButtonCodeViewer::draw(int xOffset, int yOffset, int height, int width) {
    Terminal::drawLine(xOffset, yOffset+1, 33, true, width, "Press SPACE (code 32) to exit");
    Terminal::drawLine(xOffset, yOffset+2, 33, false, width, "Last pressed key is " + std::to_string(lastCode));
}
