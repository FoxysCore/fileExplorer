//
// Created by dimon on 06.06.2026.
//

#ifndef UNTITLED_BUTTONCODEVIEWER_H
#define UNTITLED_BUTTONCODEVIEWER_H
#include "../Drawable.h"
#include "../../app/App.h"


class ButtonCodeViewer: public Drawable{
    public:
        ButtonCodeViewer(App& app);
        void draw(int xOffset, int yOffset, int height, int width) override;
        void onButton(int btn) override;
        DrawableType getType() override;
        std::string getPrompt() override;
        bool isInputDirect() override {return true;}

    private:
        int lastCode = 0;
        App* app;

};


#endif //UNTITLED_BUTTONCODEVIEWER_H