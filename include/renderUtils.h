#pragma once

namespace renderUtils {
    char** createBuffer(int width, int height);
    void deleteBuffer(char** buffer, int height);
    void clear_screen();
    void hide_cursor();
}