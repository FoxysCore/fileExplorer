//
// Created by dimon on 04.06.2026.
//

#ifndef UNTITLED_FILE_H
#define UNTITLED_FILE_H
#include <filesystem>
#include <string>
#include <vector>

class File {
    public:
        File(const std::filesystem::path& path);
        File();
        ~File();

        std::filesystem::path getPath() const;
        std::filesystem::path getFilename() const;
        bool exists() const;
        bool isDirectory() const;
        bool isFile() const;

        File getParent() const;

        void create() const;
        void remove() const;

        std::vector<File> getChildren(std::string filter, bool showHidden) const;
        std::vector<File> getChildren() const {return this->getChildren("", true);}

        bool eqals(File& file) const;

    private:
        std::filesystem::path path;
};


#endif //UNTITLED_FILE_H