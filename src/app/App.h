//
// Created by dimon on 05.06.2026.
//

#ifndef UNTITLED_APP_H
#define UNTITLED_APP_H
#include "../drawable/Drawable.h"
#include "../utils/pointedVector/PointedVector.h"

class App {
public:
    App();

    Drawable* getDrawable(int position);
    int getDrawableCount() const;
    int registerDrawable(Drawable* drawable);
    int registerDrawable(Drawable* drawable, int position);
    void unregisterDrawable(int position);

    int getSelectedDrawablePosition();
    void selectDrawable(int position);
    void onButton(int btn);

    void start();
    void stop();

private:
    PointedVector<Drawable*> drawables = PointedVector<Drawable*>();
    bool isRunning = false;
    void draw();

    void onButton(char btn);
};



#endif //UNTITLED_APP_H