//
// Created by dimon on 05.06.2026.
//
#include <string>
#include "Menu.h"
#include "../../utils.h"
#include "../buttonCodeViewer/ButtonCodeViewer.h"
#include "../files/fileManager/FileExplorer.h"


Menu::Menu(App* app) {this->app = app;}

DrawableType Menu::getType() {
    return MENU;
}

void Menu::draw(int xOffset, int yOffset, int height, int width) {
    this->setSelected(this->selected);
    switch (this->mode) {
        case MAIN: {
            drawLine(xOffset, yOffset, 33, this->selected == 0, width, "select app");
            drawLine(xOffset, yOffset + 1, 33, this->selected == 1, width, "open new tab");
            drawLine(xOffset, yOffset + 2, 33, this->selected == 2, width, "close tab");
            drawLine(xOffset, yOffset + 3, 33, this->selected == 3, width, "close menu");
            drawLine(xOffset, yOffset + 4, 33, this->selected == 4, width, "exit app");
            break;
        }

        case SELECT_APP: {
            drawLine(xOffset, yOffset, 33, this->selected == 0, width, "back to menu");
            drawLine(xOffset, yOffset + 1, 33, this->selected == 1, width, "file explorer");
            drawLine(xOffset, yOffset + 2, 33, this->selected == 2, width, "wget (http) (uncompleted)");
            drawLine(xOffset, yOffset + 3, 33, this->selected == 3, width, "wget (FTP) (uncompleted)");
            drawLine(xOffset, yOffset + 4, 33, this->selected == 4, width, "button code viewer");
            break;
        }

        case NEW_TAB_POSITION_SELECT: {
            drawLine(xOffset, yOffset, 33, this->selected == 0, width, "back to menu");
            int count = this->app->getDrawableCount();
            for (int i = 0; i < count; i++) {
                Drawable* drawable = this->app->getDrawable(i);
                drawLine(xOffset, yOffset + 1 + i, 33, this->selected == i+1, width, "V " + drawable->getPrompt());
            }
            drawLine(xOffset, yOffset + count + 1, 33, this->selected == count + 1, width, "END");
            break;
        }

        case CLOSE_TAB_SELECT: {
            drawLine(xOffset, yOffset, 33, this->selected == 0, width, "back to menu");
            int count = this->app->getDrawableCount();
            for (int i = 0; i < count; i++) {
                Drawable* drawable = this->app->getDrawable(i);
                drawLine(xOffset, yOffset + 1 + i, 33, this->selected == i+1, width, drawable->getPrompt());
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
    if (this->mode == MAIN) {this->selected = (selected + 5)%5;}
    if (this->mode == SELECT_APP) {this->selected = (selected + 5)%5;}
    if (this->mode == NEW_TAB_POSITION_SELECT) {this->selected = (selected + this->app->getDrawableCount() + 2)%(this->app->getDrawableCount() + 2);}
    if (this->mode == CLOSE_TAB_SELECT) {this->selected = (selected + this->app->getDrawableCount() + 1)%(this->app->getDrawableCount() + 1);}
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
                case 3: this->app->unregisterDrawable(this->app->getSelectedDrawablePosition()); break;
                case 4: this->app->stop(); break;
            }
            break;
        }

        case SELECT_APP: {
            switch (this->selected) {
                case 0: this->setMode(MAIN); break;
                case 1: {
                    int insertPosition = this->app->getSelectedDrawablePosition();
                    this->app->registerDrawable(new FileExplorer(app), insertPosition);
                    this->app->unregisterDrawable(insertPosition+1);
                    break;
                }
                case 4: {
                    int insertPosition = this->app->getSelectedDrawablePosition();
                    this->app->registerDrawable(new ButtonCodeViewer(app), insertPosition);
                    this->app->unregisterDrawable(insertPosition+1);
                    break;
                    }
            }
            break;
        }

        case NEW_TAB_POSITION_SELECT: {
            if (this->selected == 0) {this->setMode(MAIN);}
            else {this->app->registerDrawable(new Menu(app), this->selected-1);}
            break;
        }

        case CLOSE_TAB_SELECT: {
            if (this->selected == 0) {this->setMode(MAIN);}
            else {this->app->unregisterDrawable(this->selected-1);}
            break;
        }

    }
}