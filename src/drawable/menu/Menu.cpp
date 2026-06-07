//
// Created by dimon on 05.06.2026.
//
#include <string>
#include "Menu.h"
#include "../../utils/Terminal.hpp"
#include "../buttonCodeViewer/ButtonCodeViewer.h"
#include "../files/fileExplorer/FileExplorer.h"


Menu::Menu(App& app): Drawable(app) {}

DrawableType Menu::getType() {
    return MENU;
}

void Menu::draw(int xOffset, int yOffset, int height, int width) {
    this->setSelected(this->selected);
    switch (this->mode) {
        case MAIN: {
            Terminal::drawLine(xOffset, yOffset, 33, this->selected == 0, width, "select app");
            Terminal::drawLine(xOffset, yOffset + 1, 33, this->selected == 1, width, "open new tab");
            Terminal::drawLine(xOffset, yOffset + 2, 33, this->selected == 2, width, "close tab");
            Terminal::drawLine(xOffset, yOffset + 3, 33, this->selected == 3, width, "close menu");
            Terminal::drawLine(xOffset, yOffset + 4, 33, this->selected == 4, width, "exit app");
            break;
        }

        case SELECT_APP: {
            Terminal::drawLine(xOffset, yOffset, 33, this->selected == 0, width, "back to menu");
            Terminal::drawLine(xOffset, yOffset + 1, 33, this->selected == 1, width, "file explorer");
            Terminal::drawLine(xOffset, yOffset + 2, 33, this->selected == 2, width, "wget (http) (uncompleted)");
            Terminal::drawLine(xOffset, yOffset + 3, 33, this->selected == 3, width, "wget (FTP) (uncompleted)");
            Terminal::drawLine(xOffset, yOffset + 4, 33, this->selected == 4, width, "button code viewer");
            break;
        }

        case NEW_TAB_POSITION_SELECT: {
            Terminal::drawLine(xOffset, yOffset, 33, this->selected == 0, width, "back to menu");
            int count = this->getApp().getDrawableCount();
            for (int i = 0; i < count; i++) {
                Drawable& drawable = this->getApp().getDrawable(i);
                Terminal::drawLine(xOffset, yOffset + 1 + i, 33, this->selected == i+1, width, "V " + drawable.getPrompt());
            }
            Terminal::drawLine(xOffset, yOffset + count + 1, 33, this->selected == count + 1, width, "END");
            break;
        }

        case CLOSE_TAB_SELECT: {
            Terminal::drawLine(xOffset, yOffset, 33, this->selected == 0, width, "back to menu");
            int count = this->getApp().getDrawableCount();
            for (int i = 0; i < count; i++) {
                Drawable& drawable = this->getApp().getDrawable(i);
                Terminal::drawLine(xOffset, yOffset + 1 + i, 33, this->selected == i+1, width, drawable.getPrompt());
            }
            break;
        }
    }
}


void Menu::onButton(int btn) {
    switch (btn) {
        case 66: { //down
                this->setSelected(this->selected + 1);
                break;
            }

        case 65: { //up
                this->setSelected(this->selected - 1);
                break;
            }

        case 13: { //enter
            this->onEnter();
            break;
        }
    }
}


void Menu::setSelected(int selected) {

    int limit = 1;

    if (this->mode == MAIN) {limit = 5;}
    if (this->mode == SELECT_APP) {limit = 5;}
    if (this->mode == NEW_TAB_POSITION_SELECT) {limit = this->getApp().getDrawableCount() + 2;}
    if (this->mode == CLOSE_TAB_SELECT) {limit = this->getApp().getDrawableCount() + 1;}

    this->selected = (selected + limit)%limit;
}


void Menu::setMode(const MenuMode mode) {
    this->selected = 0;
    this->mode = mode;
}

std::string Menu::getPrompt() {
    return "Menu";
}


void Menu::onEnter() {
    switch (this->mode) {
        case MAIN: {
            switch (this->selected) {
                case 0: this->setMode(SELECT_APP); break;
                case 1: this->setMode(NEW_TAB_POSITION_SELECT); break;
                case 2: this->setMode(CLOSE_TAB_SELECT); break;
                case 3: this->getApp().removeActiveDrawable(); break;
                case 4: this->getApp().stop(); break;
            }
            break;
        }

        case SELECT_APP: {
            switch (this->selected) {
                case 0: this->setMode(MAIN); break;
                case 1: {
                    int insertPosition = this->getApp().getActiveDrawablePosition();
                    this->getApp().createDrawable(FILE_EXPLORER, insertPosition);
                    this->getApp().removeDrawable(insertPosition+1);
                    break;
                }
                case 4: {
                    int insertPosition = this->getApp().getActiveDrawablePosition();
                    this->getApp().createDrawable(BUTTON_CODE_VIEWER, insertPosition);
                    this->getApp().removeDrawable(insertPosition+1);
                    break;
                    }
            }
            break;
        }

        case NEW_TAB_POSITION_SELECT: {
            if (this->selected == 0) {this->setMode(MAIN);}
            else {this->getApp().createDrawable(MENU, this->selected - 1);}
            break;
        }

        case CLOSE_TAB_SELECT: {
            if (this->selected == 0) {this->setMode(MAIN);}
            else {this->getApp().removeDrawable(this->selected-1);}
            break;
        }

    }
}