//
// Created by dimon on 06.06.2026.
//

#include "ButtonCodeViewer.h"
#include "../../utils.h"

ButtonCodeViewer::ButtonCodeViewer(App* app): app(app) {}

std::string ButtonCodeViewer::getPrompt() {
    return "Button Code Viewer";
}

DrawableType ButtonCodeViewer::getType() {
    return BUTTON_CODE_VIEWER;
}

void ButtonCodeViewer::onButton(int btn) {
    if (btn == 32) this->app->unregisterDrawable(this->app->getSelectedDrawablePosition());
    else this->lastCode = btn;
}

void ButtonCodeViewer::draw(int xOffset, int yOffset, int height, int width) {
    drawLine(xOffset, yOffset+1, 33, true, width, "Press SPACE (code 32) to exit");
    drawLine(xOffset, yOffset+2, 33, false, width, "Last pressed key is " + std::to_string(lastCode));
}
