#include "RenderConfig.h"
#include <cmath>

namespace RenderConfig {
    // 镜头位置
    const double camera[3] = {1.0, 1.0, 5.0};
    // 旋转速度
    const double rotate_speed = 0.05;
    // buffer大小
    const int width = 100;
    const int height = 30;
    // 缩放比例，将立方体的坐标缩放到屏幕上
    const int scale_x = 15;
    const int scale_y = 7;

    // 渲染符号
    std::vector<std::pair<double,char>> symbols = {
        {0.2, '@'},
        {0.4, '*'},
        {0.6, '+'},
        {0.8, '-'},
        {1.0, '.'}
    };
}