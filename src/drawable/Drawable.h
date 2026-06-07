//
// Created by dimon on 05.06.2026.
//

#ifndef UNTITLED_DRAWABLE_H
#define UNTITLED_DRAWABLE_H
#include <string>
#include "DrawableType.h"

class App;

class Drawable
{
    private:
        App &app;

    protected:
        App& getApp() {return app;}

    public:
        Drawable(App& app) : app(app) {}
        virtual ~Drawable() = default;
        virtual void draw(int xOffset, int yOffset, int height, int width) = 0;
        virtual void onButton(int btn) = 0;
        virtual DrawableType getType() = 0;
        virtual std::string getPrompt() = 0;
        virtual bool isInputDirect() {return false;}
};


#endif //UNTITLED_DRAWABLE_H