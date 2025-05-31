#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <random>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Utils {

inline int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline void wait(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

} 

#endif 
