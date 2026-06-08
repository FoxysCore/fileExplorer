//
// Created by dimon on 08.06.2026.
//

#include "FileReader.h"

#include "../../../app/App.h"
#include "../../../utils/Terminal.hpp"

FileReader::FileReader(App& app): Drawable(app) {}

DrawableType FileReader::getType() {
    return FILE_READER;
}


void FileReader::onButton(int btn) {
    if (btn == 27) {return;}
    if (btn == 65 && lineOffset > 0) lineOffset--; //up
    else if (btn == 66 && lineOffset < this->lines.size() - 2) lineOffset++; //down
    else if (btn == 99) this->getApp().removeActiveDrawable();
}


std::string FileReader::getPrompt() {
 return "FileReader " + this->file.getFilename().string();
}


void FileReader::setFile(File& file) {
    this->file = file;
    this->content = file.read();
    this->lineOffset = 0;
    this->lines.clear();
}

void FileReader::reload() {
    this->setFile(this->file);
}

void FileReader::draw(int xOffset, int yOffset, int height, int width) {
    this->regenerateLines(width-1);

    for (int i = 0; i <= height; i++) {
        if (lineOffset + i >= this->lines.size()) {return;}
        Terminal::drawLine(xOffset, yOffset+i, 33, false, width, lines.at(i + lineOffset));
    }
}


void FileReader::regenerateLines(int width) {
    if (this->oldDrawWidth == width) {return;}
    this->oldDrawWidth = width;
    this->lines.clear();

    size_t start = 0;
    size_t len = content.length();
    size_t w = static_cast<size_t>(width);

    while (start < len) {
        size_t newline_pos = content.find('\n', start);

        size_t end = newline_pos;
        bool has_newline = (newline_pos != std::string::npos);
        if (!has_newline || (newline_pos - start) > w) {
            end = start + w;
            has_newline = false;
        }

        lines.push_back(content.substr(start, end - start));

        start = end;
        if (has_newline) {
            start++;
        }
    }

    if (lineOffset > lines.size()) {lineOffset = lines.size()-1;}
}
