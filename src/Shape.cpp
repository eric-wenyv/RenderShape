#include "Shape.h"
#include <algorithm>
#include <sstream>
#include <array>
#include <fstream>
#include <iostream>
#include <cmath>
#include "RenderConfig.h"
#include "Matrix.h"
#include <initializer_list>

std::vector<Dot> Shape::readShape(const std::string &filename)
{
    std::vector<Dot> dots;
    std::string line;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return dots; // 返回空向量
    }
    //跳过第一行标题
    getline(file, line);

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string value;

        int i{0};
        std::array<double, 3> coordinate{};
        while (getline(ss, value, ','))
        {
            coordinate[i++] = stod(value);
        }

        Dot new_dot(coordinate[0], coordinate[1], coordinate[2]);
        dots.push_back(new_dot);
    }

    return dots;
}

std::vector<Dot> Shape::readObj(const std::string &filename)
{
    std::vector<Dot> dots;
    std::vector<Dot> vertices;
    std::string line;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return dots;
    }

    while (getline(file, line))
    {
        if (line.empty()) continue;

        // 处理顶点行 "v x y z"
        if (line.substr(0, 2) == "v ")
        {
            std::stringstream ss(line);
            std::string token;
            std::vector<double> coordinates;

            // 跳过 "v" 标识符
            ss >> token;

            // 读取坐标值
            while (ss >> token)
            {
                try {
                    coordinates.push_back(std::stod(token));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid number format: '" << token << "' in line: " << line << std::endl;
                    break;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Number out of range: '" << token << "' in line: " << line << std::endl;
                    break;
                }
            }

            if (coordinates.size() >= 3)
            {
                Dot new_dot(coordinates[0], coordinates[1], coordinates[2]);
                vertices.push_back(new_dot);
            }
            else
            {
                std::cerr << "Invalid vertex format in line: " << line << std::endl;
            }
        }
        // 处理面行 "f v1 v2 v3 v4" 或 "f v1/vt1/vn1 v2/vt2/vn2 ..."
        else if (line.substr(0, 2) == "f ")
        {
            std::stringstream ss(line);
            std::string token;
            std::vector<int> face_indices;

            // 跳过 "f" 标识符
            ss >> token;

            // 读取面索引
            while (ss >> token)
            {
                std::string vertex_index = token.substr(0, token.find('/'));
                if (!vertex_index.empty()) {
                    try {
                        int index = std::stoi(vertex_index) - 1; // OBJ索引从1开始，转为从0开始
                        if (index >= 0 && index < static_cast<int>(vertices.size())) {
                            face_indices.push_back(index);
                        } else {
                            std::cerr << "Vertex index out of range: " << vertex_index << " in line: " << line << std::endl;
                            break;
                        }
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid index format: '" << vertex_index << "' in line: " << line << std::endl;
                        break;
                    }
                }
            }

            // 如果有足够的顶点索引，填充面
            if (face_indices.size() >= 4)
            {
                std::array<int, 4> vertices_indexes = {face_indices[0], face_indices[1], face_indices[2], face_indices[3]};
                fillSurface(vertices_indexes, vertices, dots);
            }
            else if (face_indices.size() == 3)
            {
                // 处理三角形面，填充第四个索引为0
                std::array<int, 4> vertices_indexes = {face_indices[0], face_indices[1], face_indices[2], 0};
                // 注意：fillSurface 需要修改以处理三角形
                std::cerr << "Warning: Triangle face detected, but fillSurface expects quads" << std::endl;
            }
        }
    }

    return dots;
}

template<typename T>
T min_multi(std::initializer_list<T> vals) {
    return *std::min_element(vals.begin(), vals.end());
}

template<typename T>
T max_multi(std::initializer_list<T> vals) {
    return *std::max_element(vals.begin(), vals.end());
}

void Shape::fillSurface(const std::array<int, 4> vertices_indexes, std::vector<Dot>& vertices, std::vector<Dot>& dots)
{
    if (vertices_indexes[3] != 0)
    {
        Dot& dot1 = vertices[vertices_indexes[0]];
        Dot& dot2 = vertices[vertices_indexes[1]];
        Dot& dot3 = vertices[vertices_indexes[2]];
        Dot& dot4 = vertices[vertices_indexes[3]];

        double min_x = min_multi({dot1.x(), dot2.x(), dot3.x(), dot4.x()});
        double min_y = min_multi({dot1.y(), dot2.y(), dot3.y(), dot4.y()});
        double min_z = min_multi({dot1.z(), dot2.z(), dot3.z(), dot4.z()});
        double max_x = max_multi({dot1.x(), dot2.x(), dot3.x(), dot4.x()});
        double max_y = max_multi({dot1.y(), dot2.y(), dot3.y(), dot4.y()});
        double max_z = max_multi({dot1.z(), dot2.z(), dot3.z(), dot4.z()});

        Matrix coefficients = Matrix::getCoefficients(dot1, dot2, dot3, dot4);

        const auto* one_array = new double[1]{1.0};
        for (double x = min_x; x <= max_x; x += 0.1)
        {
            for (double y = min_y; y <= max_y; y += 0.1)
            {
                for (double z = min_z; z <= max_z; z += 0.1)
                {
                    const auto* tmp_array = new double[3]{x, y, z};
                    Matrix point_matrix(3, 1, tmp_array);
                    Matrix result = coefficients * point_matrix;
                    Matrix expected(1, 1, one_array);
                    if (std::abs(result.at(0,0) - expected.at(0,0)) < 1e-4)
                    {
                        Dot new_dot(x, y, z);
                        dots.push_back(new_dot);
                    }
                    delete[] tmp_array;
                }
            }
        }
        delete[] one_array;
    }
}

Shape::Shape(const std::vector<Dot>& cube)
{
    this->cube = cube;
}

Shape::~Shape()
=default;

void Shape::rotate(const double rotate_speed)
{
    for (auto& dot : cube)
    {
        dot.rotate(rotate_speed);
    }
}

void Shape::render(const double camera[3],const double center[2], char*** pre_buffer
    , const int width, const int height, const double scale_x,const double scale_y)
{
    static int buffer_index = 0;
    int next_index = 1 - buffer_index;

    // 输出当前缓冲区
    std::string screen;
    screen.reserve(width * height + height);
    for (int i = 0; i < height; ++i) {
        screen.append(pre_buffer[buffer_index][i], width);
        screen.push_back('\n');
    }
    std::cout << screen;

    // 清空下一缓冲区
    for (int i = 0; i < height; ++i) {
        std::fill_n(pre_buffer[next_index][i], width, ' ');
    }

    //获得投影坐标及距离
    std::unique_ptr<int[]> pro_dot_tmp = nullptr;
    double distance = 0.0;
    auto* pro_dots_with_distance = new std::pair<std::unique_ptr<int[]>, double>[cube.size()];
    for (size_t i = 0; i < cube.size(); ++i)
    {
        pro_dot_tmp = cube[i].getProjectedCoordinates(camera, center, width, height, scale_x,scale_y);
        distance = RenderConfig::getDistanceToCamera(cube[i] ,camera);
        if (pro_dot_tmp != nullptr)
        {
            pro_dots_with_distance[i] = {std::move(pro_dot_tmp), distance};
        }
        else
        {
            pro_dots_with_distance[i] = {nullptr, 0.0};
        }
    }

    // 按照距离排序
    std::sort(pro_dots_with_distance, pro_dots_with_distance + cube.size(),
        [](const std::pair<std::unique_ptr<int[]>, double>& a, const std::pair<std::unique_ptr<int[]>, double>& b) {
        return a.second > b.second;
    });

    //归一化处理
    for (size_t i = 0; i < cube.size(); ++i)
    {

        double normalized_distance = (pro_dots_with_distance[i].second - RenderConfig::min_possible_distance) /
                                    (RenderConfig::max_possible_distance - RenderConfig::min_possible_distance);

        normalized_distance = std::max(0.0, std::min(1.0, normalized_distance));
        pro_dots_with_distance[i].second = normalized_distance;
    }

    //写入缓冲区
    for (size_t i = 0; i < cube.size(); ++i)
    {
        auto& pro_dot = pro_dots_with_distance[i].first;
        if (pro_dot != nullptr)
        {
            const int xi = pro_dot[0];
            const int yi = pro_dot[1];
            if (xi >= 0 && xi < width && yi >= 0 && yi < height)
            {
                pre_buffer[next_index][yi][xi] = RenderConfig::getSymbol(pro_dots_with_distance[i].second);
            }
        }
    }
    delete[] pro_dots_with_distance;

    buffer_index = next_index;
    std::cout.flush();
}