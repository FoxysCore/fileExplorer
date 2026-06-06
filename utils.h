//
// Created by dimon on 05.06.2026.
//
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

inline void drawLine(int x, int y, int color, bool invert, int width, const std::string& content) {
    std::cout << "\033[" << y << ";" << x << "H";
    std::cout << "\033[" << color << "m";
    if (invert) {
        std::cout << "\033[7m";
    }
    std::cout << content.substr(0, width);
    std::cout << "\033[0m" << std::flush;
}


inline void clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}
#endif //UTILS_H