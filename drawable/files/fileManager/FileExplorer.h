//
// Created by dimon on 05.06.2026.
//

#ifndef UNTITLED_FILEEXPLORER_H
#define UNTITLED_FILEEXPLORER_H
#include <set>
#include <string>

#include "FileExplorerMode.h"
#include "../../Drawable.h"
#include "../file/File.h"
#include "../../../app/App.h"

class ScreenCategory;

class FileExplorer: public Drawable {
    public:
        FileExplorer(App* app);
        void setWorkDir(File workDir);
        void draw(int xOffset, int yOffset, int height, int width) override;
        void onButton(int btn) override;
        DrawableType getType() override;
        bool isInputDirect() override;
        virtual std::string getPrompt();
        bool isFiltered(int);

    private:
        App* app;
        FileExplorerMode mode = EXPLORER;
        std::vector<File> workDir;
        std::vector<File> selectedFiles;
        File workDirFile;
        int cursorAt = 0;
        bool showHidden = false;
        std::string filter = "";
        std::string fileName = "";

        bool isFiltered(File* file);
        void normaliseCursor();
        int getSelectedFilePos(File& file);
};


#endif //UNTITLED_FILEEXPLORER_H