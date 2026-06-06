//
// Created by dimon on 05.06.2026.
//

#ifndef UNTITLED_APP_H
#define UNTITLED_APP_H
#include <vector>
#include "../drawable/Drawable.h"
#include "terminal/Terminal.hpp"

class App {
public:
    App();

    Drawable* getDrawable(int position);
    int getDrawableCount();
    int registerDrawable(Drawable* drawable);
    int registerDrawable(Drawable* drawable, int position);
    void unregisterDrawable(int position);

    int getSelectedDrawablePosition() const;
    void selectDrawable(int position);
    void onButton(int btn);

    void start();
    void stop();

private:
    int selectedDrawable = 0;
    Terminal terminal;
    std::vector<Drawable*> drawables = std::vector<Drawable*>();
    bool isRunning = false;
    void draw();

    void onButton(char btn);
};



#endif //UNTITLED_APP_H