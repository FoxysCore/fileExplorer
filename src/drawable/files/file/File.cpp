//
// Created by dimon on 05.06.2026.
//

#include "File.h"
#include <filesystem>
#include <fstream>

#include "../../../utils/pointedVector/PointedVector.h"

File::File(const std::filesystem::path& path) {
    this->path = path;
}

File::File() {
    this->path = std::filesystem::current_path();
}

File::~File() {}

bool File::exists() const {
    return std::filesystem::exists(path);
}

bool File::isFile() const {
    return std::filesystem::is_regular_file(path);
}

bool File::isDirectory() const {
    return !this->isFile();
}

std::filesystem::path File::getFilename() const {
    return this->path.filename();
}

std::filesystem::path File::getPath() const {
    return this->path;
}

File File::getParent() const {
    return File(this->path.parent_path());
}

void File::create() const {
    if (exists()) {return;}

    if (this->isDirectory()) {
        std::filesystem::create_directories(path);
    } else {
        std::filesystem::create_directories(path.parent_path());
        std::ofstream file(this->getPath());
    }
}

void File::remove() const {
    std::filesystem::remove_all(path);
}

PointedVector<File> File::getChildren(std::string filter, bool showHidden) const {
    auto children = PointedVector<File>();

    children.add(File(this->path.parent_path()));
    if (!this->isDirectory()) {return children;}
    if (!this->exists()) {return children;}
    std::filesystem::directory_iterator dir_iter(this->getPath());
    for (const std::filesystem::path entry : dir_iter) {

        if (!filter.empty() && entry.string().find(filter) == std::string::npos) {continue;}
        if (!showHidden && entry.filename().string().at(0) == '.') {continue;}

        children.add(File(entry));
    }
    return children;
}



bool File::eqals(File& file) const{
    return this->path.string() == file.getPath().string();
}


long File::getSize() const {
    if (this->isDirectory()) {return this->getChildren().size() - 1;}
    if (!this->exists()) {return 0;}
    return std::filesystem::file_size(path);
}

std::string File::read() const {
    if (!this->exists() || !this->isFile()) {return "nothing to read";}
    if (this->getSize() > 1024*128) {return "too big to read :(";}

    std::ifstream file(this->path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();

    file.seekg(0, std::ios::beg);
    std::string content(size, '\0');

    if (size > 0) {file.read(content.data(), size);}

    return content;
}

