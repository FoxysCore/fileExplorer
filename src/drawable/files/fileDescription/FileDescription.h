//
// Created by dimon on 06.06.2026.
//

#ifndef UNTITLED_FILEDESCRIPTION_H
#define UNTITLED_FILEDESCRIPTION_H

#include "../../Drawable.h"
#include "../file/File.h"
#include "../../../app/App.h"

class FileDescription: public Drawable{
    public:
        FileDescription(App* app, File* file);
        void draw(int xOffset, int yOffset, int height, int width) override;
        void onButton(int btn) override;
        DrawableType getType() override;
        std::string getPrompt() override;
        bool isInputDirect() override {return false;}

    private:
        App* app;

        bool isDir;

        std::string filename;
        std::string filepath;
        long filesize;
};


#endif //UNTITLED_FILEDESCRIPTION_H