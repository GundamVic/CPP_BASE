#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

struct Point
{
    double x;
    double y;
};

// 辅助函数：判断点和多边形边的关系（左侧、右侧或在线上）
double isLeft(const Point &p1, const Point &p2, const Point &p)
{
    return (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);
}

// 计算点是否在非简单多边形内
int isPointInPolygonWinding(const Point &p, const std::vector<Point> &polygon)
{
    double winding_number = 0; // 总的旋转角度

    size_t vertex_count = polygon.size();
    if (vertex_count < 3)
    {
        return 0; // 不构成多边形
    }

    for (size_t i = 0; i < vertex_count; ++i)
    {
        const Point &p1 = polygon[i];                      // 当前顶点
        const Point &p2 = polygon[(i + 1) % vertex_count]; // 下一个顶点

        // 判断边的关系
        if (p1.y <= p.y)
        {
            if (p2.y > p.y && isLeft(p1, p2, p) > 0)
            {
                // 射线穿过边，逆时针角度变化
                winding_number += 1;
            }
        }
        else
        {
            if (p2.y <= p.y && isLeft(p1, p2, p) < 0)
            {
                // 射线穿过边，顺时针角度变化
                winding_number -= 1;
            }
        }
    }

    // 如果环绕次数非零，点在多边形内
    return winding_number != 0;
}

// 可视化多边形和测试点
void visualizePolygon(const std::vector<Point> &polygon, const Point &test_point, bool is_inside)
{
    // 创建一个空白图像
    int width = 800, height = 600;
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    // 绘制多边形的边
    for (size_t i = 0; i < polygon.size(); ++i)
    {
        const Point &p1 = polygon[i];
        const Point &p2 = polygon[(i + 1) % polygon.size()]; // 封闭路径
        cv::line(image,
                 cv::Point(static_cast<int>(p1.x * 50), static_cast<int>(p1.y * 50)), // 放大坐标以适应图像范围
                 cv::Point(static_cast<int>(p2.x * 50), static_cast<int>(p2.y * 50)),
                 cv::Scalar(255, 0, 0), 2); // 蓝色线
    }

    // 绘制多边形的顶点
    for (const auto &vertex : polygon)
    {
        cv::circle(image,
                   cv::Point(static_cast<int>(vertex.x * 50), static_cast<int>(vertex.y * 50)),
                   5, cv::Scalar(0, 0, 255), -1); // 红色点
    }

    // 绘制测试点
    cv::circle(image,
               cv::Point(static_cast<int>(test_point.x * 50), static_cast<int>(test_point.y * 50)),
               8, is_inside ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 0), -1); // 绿色点表示在内，黑色点表示在外

    // 在窗口显示图像
    cv::imshow("Polygon Visualization", image);
    cv::waitKey(0); // 按下任意键关闭窗口
}

int main()
{
    // 非简单多边形示例
    std::vector<Point> polygon = {
        {0, 0}, {10, 0}, {5, 5}, {10, 10}, {0, 10}, {5, 5} // 有自交点
    };

    // 测试点
    Point test_point_inside = {5, 6};   // 位于多边形内部
    Point test_point_outside = {15, 5}; // 位于多边形外
    Point test_point_edge = {5, 5};     // 位于边上的自交点

    // 测试点计算
    bool inside = isPointInPolygonWinding(test_point_inside, polygon);
    std::cout << "Test point (5, 6): Inside = " << inside << "\n";

    // 可视化内部点
    visualizePolygon(polygon, test_point_inside, inside);

    // 测试点计算
    inside = isPointInPolygonWinding(test_point_outside, polygon);
    std::cout << "Test point (15, 5): Inside = " << inside << "\n";

    // 可视化外部点
    visualizePolygon(polygon, test_point_outside, inside);

    // 测试边界点
    inside = isPointInPolygonWinding(test_point_edge, polygon);
    std::cout << "Test point (5, 5) on edge: Inside = " << inside << "\n";

    // 可视化边界点
    visualizePolygon(polygon, test_point_edge, inside);

    return 0;
}
