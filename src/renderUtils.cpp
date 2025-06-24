#include <algorithm>
#include <iostream>
#include "renderUtils.h"

namespace renderUtils {
char** createBuffer(const int width, const int height) {
    const auto buffer = new char*[height];
    for (int i = 0; i < height; ++i) {
        buffer[i] = new char[width];
        std::fill_n(buffer[i], width, ' ');
    }
    return buffer;
}

void deleteBuffer(char** buffer, const int height)
{
    for (int i = 0; i < height; ++i) {
        delete[] buffer[i];
    }
    delete[] buffer;
}

void clear_screen()
{
    std::cout << "\033[H";
    std::cout.flush();
}

void hide_cursor()
{
    std::cout << "\033[?25l"; // 隐藏光标
    std::cout.flush();
}
}
