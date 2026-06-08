//
// Created by dimon on 08.06.2026.
//

#ifndef UNTITLED_FILEREADER_H
#define UNTITLED_FILEREADER_H
#include "../../Drawable.h"
#include "../file/File.h"
#include "../../DrawableType.h"

class FileReader : public Drawable {

    public:
        FileReader(App& app);
        void setFile(File& file);
        void reload();
        void draw(int xOffset, int yOffset, int height, int width) override;
        void onButton(int btn) override;
        DrawableType getType() override;
        std::string getPrompt() override;
        bool isInputDirect() override {return false;}

    private:
        File file = File();
        std::string content = "";
        std::vector<std::string> lines = std::vector<std::string>();
        int lineOffset = 0;
        int oldDrawWidth = 0;

        void regenerateLines(int width);
};


#endif //UNTITLED_FILEREADER_H