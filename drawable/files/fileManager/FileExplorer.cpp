//
// Created by dimon on 05.06.2026.
//

#include "FileExplorer.h"
#include <format>
#include "../../../utils.h"
#include "../fileDescription/FileDescription.h"

FileExplorer::FileExplorer(App* app): app(app)  {
    this->setWorkDir(File());
}

bool FileExplorer::isInputDirect() {
    return this->mode == FILTER_ENTER;
}

void FileExplorer::setWorkDir(const File workDir) {
    if (!workDir.isDirectory()) {return;}
    this->workDir = workDir.getChildren(this->filter, this->showHidden);
    if (workDir.eqals(this->workDirFile)) {
        this->normaliseCursor();
        return;
    }
    this->workDirFile = workDir;
    this->cursorAt = 0;
}

void FileExplorer::draw(int xOffset, int yOffset, int height, int width) {
    File dir = this->workDirFile;
    while (!dir.exists()) {
        dir = dir.getParent();
    }
    this->setWorkDir(dir);

    std::vector<File>* forRender = &this->workDir;


    if (this->mode == FILE_REMOVE) {
        drawLine(xOffset, yOffset + height, 33, true, width, "Are you SURE you want to DELETE this? (y/n)");
        forRender = &this->selectedFiles;
        height -= 1;
    }


    else if (this->mode == FILTER_ENTER) {
        auto out = "f> " + this->filter;
        while (out.size() < width) {out.append(" ");}
        drawLine(xOffset, yOffset + height, 33, true, width, out);
        height -= 1;
    }

    else if (this->mode == FILE_CREATING) {
        auto out = "+> " + this->fileName;
        while (out.size() < width) {out.append(" ");}
        drawLine(xOffset, yOffset + height, 33, true, width, out);
        height -= 1;
    }

    int page = this->cursorAt/(height+1);
    int startIndex = page*(height+1);



    for (int i = 0; startIndex + i < forRender->size() && i <= height; i++) {
        File& file = forRender->at(startIndex+i);
        std::string fileName = file.getFilename();

        if (this->mode == FILE_REMOVE) {
            fileName = file.getPath();
            if (fileName.size() > width-8) {
                fileName = "..." + fileName.substr(8, fileName.size());
            }
        }

        else if (startIndex + i == 0) {fileName = "/..";}

        fileName = (file.isDirectory()? " ": " ") + fileName;
        if (this->getSelectedFilePos(file) != -1) {fileName = " * " + fileName;}

        drawLine(
            xOffset,
            yOffset + i,
            33,
            i + startIndex == cursorAt && this->mode != FILE_REMOVE,
            width,
            fileName
            );
    }

}

void FileExplorer::onButton(int btn) {
    switch (btn) {
        case 100: //d
            if (this->mode != EXPLORER) {break;}
            this->mode = FILE_REMOVE;
            if (this->selectedFiles.empty()) {
                this->selectedFiles.push_back(this->workDir.at(this->cursorAt));
            }

        case 65: //up
            this->cursorAt --;
            this->normaliseCursor();
            break;

        case 66: //down
            this->cursorAt ++;
            this->normaliseCursor();
            break;

        case 13: //enter
            this->setWorkDir(this->workDir.at(this->cursorAt));
            return;

        case 46: this->showHidden = !this->showHidden; break; //.

        case 102: { //f
            if (this->mode == EXPLORER) {
                this->mode = FILTER_ENTER;
                return;
            }
        }

        case 115: { //s
            if (this->mode != EXPLORER) {break;}
            File& file = this->workDir.at(this->cursorAt);

            int filePos = this->getSelectedFilePos(file);
                if (filePos >= 0) {
                    this->selectedFiles.erase(this->selectedFiles.begin() + filePos);
                    return;
                }

            if (!file.exists()) {break;}
            this->selectedFiles.push_back(file);
            break;
        }

        case 43: {//+
            if (this->mode == EXPLORER) {
                this->mode = FILE_CREATING;
                return;
            }
            if (this->mode == FILE_CREATING) {
                File(this->workDirFile.getPath().append(this->fileName)).create();
                this->fileName.clear();
            }
        }

        case 72: this->cursorAt = 0; break; //Home

        case 27: this->mode = EXPLORER; break; //Esc

        case 9: //TAB
            this->app->registerDrawable(new FileDescription(app, &this->workDir.at(this->cursorAt)));
            break;
    }

    if (this->mode == FILTER_ENTER) {
        if (btn == 127) this->filter = this->filter.substr(0, this->filter.size()-1);
        else this->filter += (char) btn;
    }

    if (this->mode == FILE_CREATING) {
        if (btn == 127) this->fileName = this->fileName.substr(0, this->fileName.size()-1);
        else this->fileName += (char) btn;
    }

    if (this->mode == FILE_REMOVE) {
        if (btn == 121) { //y
            if (this->selectedFiles.empty()) {
                this->workDir.at(this->cursorAt).remove();
            }
            for (File& file : this->selectedFiles) {
                file.remove();
            }
            this->selectedFiles.clear();
            this->mode = EXPLORER;
        } else if (btn == 110) { //n
            this->mode = EXPLORER;
        }
    }



}

DrawableType FileExplorer::getType() {
    return FILE_EXPLORER;
}


std::string FileExplorer::getPrompt() {
    return "File Explorer " + this->workDirFile.getPath().string();
}


void FileExplorer::normaliseCursor() {
    while (this->cursorAt < 0) {this->cursorAt += this->workDir.size();}
    this->cursorAt = this->cursorAt%this->workDir.size();
}


int FileExplorer::getSelectedFilePos(File& file) {
    for (int selectedFileId = 0; selectedFileId < this->selectedFiles.size(); selectedFileId++) {
        File& selectedFile = this->selectedFiles.at(selectedFileId);
        if (file.eqals(selectedFile)) {
            return selectedFileId;
        }
    }
    return -1;
}
