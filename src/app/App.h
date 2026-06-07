//
// Created by dimon on 05.06.2026.
//

#ifndef UNTITLED_APP_H
#define UNTITLED_APP_H
#include <memory>

#include "../utils/pointedVector/PointedVector.h"
#include "../drawable/DrawableType.h"
#include "../drawable/Drawable.h"

class App {
public:
    App();
    ~App();

    Drawable& createDrawable(DrawableType type, int position);
    Drawable& getDrawable(int position);
    Drawable& getActiveDrawable();
    int getActiveDrawablePosition();
    int getDrawableCount();

    void removeDrawable(int position);
    void removeActiveDrawable();
    void selectDrawable(int position);

    void onButton(int btn);

    void start();
    void stop();

private:
    PointedVector<std::unique_ptr<Drawable>> drawables = PointedVector<std::unique_ptr<Drawable>>();
    bool isRunning = false;
    void draw();

    void onButton(char btn);
};



#endif //UNTITLED_APP_H