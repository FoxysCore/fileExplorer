//
// Created by dimon on 05.06.2026.
//

#include "App.h"
#include "../utils.h"
#include "../drawable/menu/Menu.h"

#include "../drawable/files/file/File.h"

App::App() : terminal(Terminal()) {
    this->registerDrawable(new Menu(this));
}

Drawable* App::getDrawable(int position) {
    return this->drawables.at(position);
}

int App::getDrawableCount() {
    return this->drawables.size();
}

int App::registerDrawable(Drawable* drawable) {
    this->drawables.push_back(drawable);
    return this->drawables.size()-1;
}

int App::registerDrawable(Drawable* drawable, int position) {
    if (position < 0) {position = 0;}
    if (position > this->getDrawableCount()) {position = this->getDrawableCount();}
    this->drawables.insert(this->drawables.begin() + position, drawable);
    return this->drawables.size()-1;
}

void App::unregisterDrawable(int position) {
    Drawable* drawable = this->drawables.at(position);
    this->drawables.erase(this->drawables.begin() + position);
    delete drawable;
    this->selectDrawable(this->getSelectedDrawablePosition());
}

int App::getSelectedDrawablePosition() const {
    return this->selectedDrawable;
}

void App::selectDrawable(int position) {
    if (this->getDrawableCount() == 0) {
        this->selectedDrawable = 0;
        return;
    }
    while (position < 0) {position += this->getDrawableCount();}
    position = position%this->getDrawableCount();
    this->selectedDrawable = position;
}

void App::start() {
    this->terminal.getSize();

    this->isRunning = true;
    while (isRunning) {
        this->draw();
        this->onButton(terminal.getButton());
    }
    clearScreen();
}

void App::stop() {
    this->isRunning = false;
}

void App::onButton(int btn) {
    Drawable* drawable = this->getDrawable(this->getSelectedDrawablePosition());

    if (drawable->isInputDirect()) {
        drawable->onButton(btn);
        return;
    }

    switch (btn) {
        case 3: this->stop(); return; //CTRL + c
        case 4: this->stop(); return; //CTRL + d
        case 109: this->registerDrawable(new Menu(this)); this->unregisterDrawable(0); return; //m
        case 77: this->registerDrawable(new Menu(this)); return; //M

        case 67: this->selectDrawable(this->getSelectedDrawablePosition() + 1); return; //->
        case 68: this->selectDrawable(this->getSelectedDrawablePosition() - 1); return; //<-

    }

    drawable->onButton(btn);
}


void App::draw() {
    clearScreen();
    auto size = this->terminal.getSize();
    int height = size.second, width = size.first;
    int drawableWidth = width/this->getDrawableCount();

    for (int space = 0; space < this->getDrawableCount(); space++) {
        Drawable* drawable = this->getDrawable(space);
        int drawingX = space*drawableWidth + 1;

        drawLine( //title
            drawingX,
            1,
            33,
            space == this->getSelectedDrawablePosition(),
            drawableWidth,
            drawable->getPrompt()
            );

        drawable->draw( //main frame
            drawingX,
            2,
            height-2,
            drawableWidth
            );

        for (int i = 1; i <= height && space != 0; i++) {
            drawLine(drawableWidth*space, i, 33, false, 100, "|");
        }
    }
}
