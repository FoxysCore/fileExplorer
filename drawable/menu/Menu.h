//
// Created by dimon on 05.06.2026.
//

#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H
#include <string>
#include "../Drawable.h"
#include "MenuMode.h"
#include "../../app/App.h"


class Menu: public Drawable {
    public:
        Menu(App* app);
        void draw(int xOffset, int yOffset, int height, int width) override;
        void onButton(int btn) override;
        DrawableType getType() override;
        std::string getPrompt() override;

        void setSelected(int selected);

        void setMode(MenuMode mode);

    private:
        App* app;
        MenuMode mode = MenuMode::MAIN;
        int selected = 0;

        void onEnter();
};


#endif //UNTITLED_MENU_H