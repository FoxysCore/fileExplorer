//
// Created by dimon on 06.06.2026.
//

#include "FileDescription.h"
#include "../../../utils.h"

FileDescription::FileDescription(App* app, File* file) : app(app)
{

    for (int i = 0; i < app->getDrawableCount(); i++) {
        Drawable* drawable = app->getDrawable(i);
        if (drawable->getType() == FILE_DESCRIPTION) {
            app->unregisterDrawable(i);
            break;
        }
    }

    filename = file->getFilename();
    filepath = file->getPath();
    isDir = file->isDirectory();
    if (isDir)
        filesize = file->getChildren().size();
    else
        filesize = file->getSize();
}

std::string FileDescription::getPrompt() {return "File Info";}

DrawableType FileDescription::getType() {return FILE_DESCRIPTION;}

void FileDescription::onButton(int btn) {this->app->unregisterDrawable(app->getSelectedDrawablePosition());}

void FileDescription::draw(int xOffset, int yOffset, int height, int width)
{
    drawLine(xOffset, yOffset+1, 33, true, width, "Type:");
    drawLine(xOffset+6, yOffset+1, 33, false, width - 6, this->isDir ? "Directory  " : "File  ");

    drawLine(xOffset, yOffset+2, 33, true, width, "Name:");
    drawLine(xOffset+6, yOffset+2, 33, false, width - 6, this->filename);

    drawLine(xOffset, yOffset+3, 33, true, width, "Size:");
    drawLine(xOffset+6, yOffset+3, 33, false, width - 6, std::to_string(filesize));

    drawLine(xOffset, yOffset+4, 33, true, width, "Path:");
    drawLine(xOffset+6, yOffset+4, 33, false, width - 6, filepath);

    int len = this->filepath.length() - width + 6;
    int lineOffset = 0;
    while (len > 0) {
        drawLine(xOffset, yOffset + 5 + lineOffset, 33, false, width, filepath.substr(lineOffset*width, (lineOffset+1)*width));
        len -= width + 6;
    }

}
