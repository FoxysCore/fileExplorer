//
// Created by dimon on 05.06.2026.
//

#include "File.h"
#include <filesystem>
#include <fstream>

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

std::vector<File> File::getChildren(std::string filter, bool showHidden) const {
    auto children = std::vector<File>();

    children.push_back(File(this->path.parent_path()));
    if (!this->isDirectory()) {return children;}
    if (!this->exists()) {return children;}
    std::filesystem::directory_iterator dir_iter(this->getPath());
    for (const std::filesystem::path entry : dir_iter) {

        if (!filter.empty() && entry.string().find(filter) == std::string::npos) {continue;}
        if (!showHidden && entry.filename().string().at(0) == '.') {continue;}

        children.push_back(File(entry));
    }
    return children;
}



bool File::eqals(File& file) const{
    return this->path.string() == file.getPath().string();
}


long File::getSize() const {
    if (this->isDirectory()) {return 0;}
    if (!this->exists()) {return 0;}
    return std::filesystem::file_size(path);
}


