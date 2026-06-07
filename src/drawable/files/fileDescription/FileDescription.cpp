//
// Created by dimon on 06.06.2026.
//

#include "FileDescription.h"
#include "../../../utils/Terminal.hpp"
#include "../../../app/App.h"


FileDescription::FileDescription(App& app) : Drawable(app) {}


void FileDescription::setFile(File& file) {
    this->file = file;
}

std::string FileDescription::getPrompt() {return "File Info";}

DrawableType FileDescription::getType() {return FILE_DESCRIPTION;}

void FileDescription::onButton(int btn) {
    this->getApp().removeDrawable(this->getApp().getActiveDrawablePosition());
}

void FileDescription::draw(int xOffset, int yOffset, int height, int width)
{
    bool isDir = file.isDirectory();
    long filesize = file.getSize();

    std::string filepath = file.getPath();

    Terminal::drawLine(xOffset, yOffset+1, 33, true, width, "Type:");
    Terminal::drawLine(xOffset+6, yOffset+1, 33, false, width - 6, isDir ? "Directory  " : "File  ");

    Terminal::drawLine(xOffset, yOffset+2, 33, true, width, "Name:");
    Terminal::drawLine(xOffset+6, yOffset+2, 33, false, width - 6, this->file.getFilename());

    Terminal::drawLine(xOffset, yOffset+3, 33, true, width, "Size:");
    Terminal::drawLine(xOffset+6, yOffset+3, 33, false, width - 6, std::to_string(filesize));

    Terminal::drawLine(xOffset, yOffset+4, 33, true, width, "Path:");
    Terminal::drawLine(xOffset+6, yOffset+4, 33, false, width - 6, filepath);

    int len = filepath.length() - width + 6;
    int lineOffset = 0;
    while (len > 0) {
        Terminal::drawLine(xOffset, yOffset + 5 + lineOffset, 33, false, width, filepath.substr(lineOffset*width, (lineOffset+1)*width));
        len -= width + 6;
    }

}
