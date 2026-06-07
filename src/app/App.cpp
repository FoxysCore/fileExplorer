//
// Created by dimon on 05.06.2026.
//


#include "App.h"

#include <memory>

#include "../drawable/files/fileExplorer/FileExplorer.h"
#include "../drawable/menu/Menu.h"
#include "../utils/pointedVector/PointedVector.h"
#include "../utils/Terminal.hpp"
#include "../drawable/DrawableType.h"
#include "../drawable/files/fileDescription/FileDescription.h"
#include "../drawable/Drawable.h"
#include "../drawable/buttonCodeViewer/ButtonCodeViewer.h"

App::App() {
    Terminal::setRawMode();
    this->createDrawable(MENU, 0);
}


Drawable& App::createDrawable(DrawableType type, int position) {
    switch (type)
    {
    case FILE_EXPLORER:
        this->drawables.insert(position, std::make_unique<FileExplorer>(*this));
        break;

    case MENU:
        this->drawables.insert(position, std::make_unique<Menu>(*this));
        break;

    case FILE_DESCRIPTION:
        this->drawables.insert(position, std::make_unique<FileDescription>(*this));
        break;

    case BUTTON_CODE_VIEWER:
        drawables.insert(position, std::make_unique<ButtonCodeViewer>(*this));
        break;
    }

    return *drawables.get(position);
}

Drawable& App::getDrawable(int position) {
    return *drawables.get(position);
}

Drawable& App::getActiveDrawable() {
    return *drawables.getSelected();
}

int App::getActiveDrawablePosition() {
    return drawables.getPointer();
}

int App::getDrawableCount() {
    return drawables.size();
}

void App::removeDrawable(int position) {
    if (drawables.size() == 1) {
        this->createDrawable(MENU, 1);
    }
    drawables.remove(position);
}

void App::removeActiveDrawable() {
    drawables.remove(drawables.getPointer());
}

void App::selectDrawable(int position) {
    drawables.select(position);
}

void App::start() {
    this->isRunning = true;
    while (isRunning) {
        this->draw();
        this->onButton(Terminal::getButton());
    }
    Terminal::clearScreen();
}

void App::stop() {
    this->isRunning = false;
}

void App::onButton(int btn) {
    Drawable& drawable = this->getActiveDrawable();

    if (drawable.isInputDirect()) {
        drawable.onButton(btn);
        return;
    }

    switch (btn) {
        case 3: this->stop(); return; //CTRL + c
        case 4: this->stop(); return; //CTRL + d
        case 109: { //m
                int position = this->getActiveDrawablePosition();
                this->createDrawable(MENU, position);
                this->removeDrawable(position+1);
                return;
            }
        case 77: { //M
                this->createDrawable(MENU, this->getDrawableCount());
                this->selectDrawable(this->getDrawableCount()-1);
                return;
            }

        case 67: drawables.stepForward(); return; //->
        case 68: drawables.stepBackward(); return; //<-

    }

    drawable.onButton(btn);
}

void App::draw() {
    Terminal::clearScreen();
    auto size = Terminal::getSize();
    int height = size.second, width = size.first;
    int drawableWidth = width/this->getDrawableCount();

    for (int space = 0; space < this->getDrawableCount(); space++) {
        Drawable& drawable = this->getDrawable(space);
        int drawingX = space*drawableWidth + 1;

        Terminal::drawLine( //title
            drawingX,
            1,
            33,
            space == drawables.getPointer(),
            drawableWidth,
            drawable.getPrompt()
            );

        drawable.draw( //main frame
            drawingX,
            2,
            height-2,
            drawableWidth
            );

        for (int i = 1; i <= height && space != 0; i++) {
            Terminal::drawLine(drawableWidth*space, i, 33, false, 100, "|");
        }
    }
}

App::~App() = default;