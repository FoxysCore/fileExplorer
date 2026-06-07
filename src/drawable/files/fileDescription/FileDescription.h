//
// Created by dimon on 06.06.2026.
//

#ifndef UNTITLED_FILEDESCRIPTION_H
#define UNTITLED_FILEDESCRIPTION_H

#include "../../Drawable.h"
#include "../file/File.h"
#include "../../DrawableType.h"

class FileDescription: public Drawable{
    public:
        FileDescription(App& app);
        void setFile(File& file);
        void draw(int xOffset, int yOffset, int height, int width) override;
        void onButton(int btn) override;
        DrawableType getType() override;
        std::string getPrompt() override;
        bool isInputDirect() override {return false;}

    private:
        File file;
};


#endif //UNTITLED_FILEDESCRIPTION_H