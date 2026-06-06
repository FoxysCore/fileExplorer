cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        drawable/files/file/File.h
        drawable/files/fileManager/FileExplorer.cpp
        drawable/files/fileManager/FileExplorer.h
        drawable/Drawable.h
        drawable/DrawableType.h
        drawable/files/file/File.cpp
        app/App.cpp
        app/App.h
        utils.h
        drawable/menu/Menu.cpp
        drawable/menu/Menu.h
        drawable/menu/MenuMode.h
        app/terminal/Terminal.hpp
        drawable/files/fileManager/FileExplorerMode.h
        drawable/buttonCodeViewer/ButtonCodeViewer.cpp
        drawable/buttonCodeViewer/ButtonCodeViewer.h
)
