#include "RenderConfig.h"
#include <cmath>

namespace RenderConfig {
    // 镜头位置
    const double camera[3] = {0.0, 0.0, 10.0};
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

    //归一化距离
    const double max_possible_distance = 10;
    const double min_possible_distance = 0;

    double getDistanceToCamera(const Dot& dot,const double camera[])
    {
        return std::sqrt(
            std::pow(dot.x() - camera[0], 2) +
            std::pow(dot.y() - camera[1], 2) +
            std::pow(dot.z() - camera[2], 2)
        );
    }

    char getSymbol(const double distance)
    {
        for (auto [dis,symbol] : RenderConfig::symbols)
        {
            if (distance <= dis)
            {
                return symbol;
            }
        }

        return ' ';
    }
}