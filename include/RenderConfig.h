#pragma once
#include <vector>
#include <utility>
#include "Dot.h"

namespace RenderConfig {
    // 镜头位置
    extern const double camera[3];
    // 旋转速度
    extern const double rotate_speed;
    // buffer大小
    extern const int width;
    extern const int height;
    // 缩放比例
    extern const int scale_x;
    extern const int scale_y;

    // 渲染符号
    extern std::vector<std::pair<double,char>> symbols;

    extern double getDistanceToCamera(const Dot& dot,const double camera[]);

    extern char getSymbol(double distance);
}