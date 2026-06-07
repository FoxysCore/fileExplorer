cmake_minimum_required(VERSION 4.1)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled src/main.cpp
        src/drawable/files/file/File.h
        src/drawable/files/fileManager/FileExplorer.cpp
        src/drawable/files/fileManager/FileExplorer.h
        src/drawable/Drawable.h
        src/drawable/DrawableType.h
        src/drawable/files/file/File.cpp
        src/app/App.cpp
        src/app/App.h
        utils.h
        src/drawable/menu/Menu.cpp
        src/drawable/menu/Menu.h
        src/drawable/menu/MenuMode.h
        src/utils/Terminal.hpp
        src/drawable/files/fileManager/FileExplorerMode.h
        src/drawable/buttonCodeViewer/ButtonCodeViewer.cpp
        src/drawable/buttonCodeViewer/ButtonCodeViewer.h
        src/drawable/files/fileDescription/FileDescription.cpp
        src/drawable/files/fileDescription/FileDescription.h
        src/utils/pointedVector/PointedVector.h
)
