// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h> // 使用 sleep 函数时需要包含此头文件

// void *thread_function(void *arg)
// {
//     int thread_id = *(int *)arg; // 获取线程 ID
//     printf("Thread %d is running...\n", thread_id);
//     sleep(2); // 模拟线程执行任务
//     printf("Thread %d has finished.\n", thread_id);
//     return NULL;
// }

// int main()
// {
//     const int num_threads = 3; // 创建 3 个线程
//     pthread_t threads[num_threads];
//     int thread_ids[num_threads];

//     // 创建线程
//     for (int i = 0; i < num_threads; ++i)
//     {
//         thread_ids[i] = i + 1; // ID 从 1 开始
//         if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0)
//         {
//             perror("Failed to create thread.");
//             exit(1);
//         }
//     }

//     // 等待线程结束
//     for (int i = 0; i < num_threads; ++i)
//     {
//         pthread_join(threads[i], NULL);               // 阻塞等待子线程结束
//         printf("Thread %d joined.\n", thread_ids[i]); // 线程结束时打印信息
//     }

//     printf("All threads have finished. Main thread continues...\n");
//     return 0;
// }

// #include <iostream>
// #include <mutex>
// #include <thread>
// #include <vector>

// class SharedResource
// {
// private:
//     mutable std::mutex mutex_; // 互斥锁
//     int shared_data_;          // 共享资源

// public:
//     SharedResource() : shared_data_(0) {}

//     void increment()
//     {
//         // 使用 std::lock_guard 加锁
//         std::lock_guard<std::mutex> lock(mutex_);

//         // 临界区：对共享数据进行操作
//         shared_data_++;
//         std::cout << "Shared data incremented to: " << shared_data_ << " by thread " << std::this_thread::get_id() << std::endl;
//     }

//     int getData()
//     {
//         // 使用 std::lock_guard 加锁，确保线程安全
//         std::lock_guard<std::mutex> lock(mutex_);
//         return shared_data_;
//     }
// };

// int main()
// {
//     SharedResource resource;

//     // 创建多个线程，并对共享资源执行操作
//     std::vector<std::thread> threads;
//     for (int i = 0; i < 5; ++i)
//     {
//         threads.emplace_back([&resource]()
//                              { resource.increment(); });
//     }

//     // 等待线程完成
//     for (auto &t : threads)
//     {
//         t.join();
//     }

//     std::cout << "Final shared data: " << resource.getData() << std::endl;

//     return 0;
// }

// #include <iostream>
// #include <mutex>
// #include <thread>

// std::mutex mutexA;
// std::mutex mutexB;
// int sharedData1 = 0;
// int sharedData2 = 0;

// void safeIncrement()
// {
//     std::lock_guard<std::mutex> lockA(mutexA);
//     std::lock_guard<std::mutex> lockB(mutexB);
//     ++sharedData1;
//     ++sharedData2;
// }

// int main()
// {
//     std::thread t1(safeIncrement);
//     std::thread t2(safeIncrement);

//     t1.join();
//     t2.join();

//     std::cout << "Result: " << sharedData1 << ", " << sharedData2 << std::endl;
//     return 0;
// }

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 定义点的结构体
struct Point2D
{
    double x, y;
};

// 判断点是否在多边形内 (射线法)
bool isPointInPolygon(const Point2D &p, const vector<Point2D> &polygon)
{
    int n = polygon.size();
    bool oddCount = false; // 交点计数为奇数时，点在多边形内部

    for (int i = 0; i < n; ++i)
    {
        Point2D p1 = polygon[i];
        Point2D p2 = polygon[(i + 1) % n];

        if ((p1.y <= p.y && p2.y > p.y) || (p2.y <= p.y && p1.y > p.y))
        {
            double xIntersect = p1.x + (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            if (xIntersect > p.x)
            {
                oddCount = !oddCount;
            }
        }
    }
    return oddCount;
}

// 将 Point2D 转换为 OpenCV 的 Point
Point convertToCvPoint(const Point2D &p)
{
    return Point(static_cast<int>(p.x), static_cast<int>(p.y));
}

int main()
{
    // 定义多边形和测试点
    vector<Point2D> polygon = {
        {100, 100}, {300, 100}, {300, 300}, {100, 300}};
    Point2D testPoint = {150, 150}; // 测试点

    // 创建空白图像
    int width = 500, height = 500;
    Mat image(height, width, CV_8UC3, Scalar(255, 255, 255));

    // 绘制多边形
    vector<Point> cvPolygon;
    for (const auto &p : polygon)
    {
        cvPolygon.push_back(convertToCvPoint(p));
    }
    polylines(image, cvPolygon, true, Scalar(0, 0, 255), 2); // 红色多边形

    // 绘制测试点
    circle(image, convertToCvPoint(testPoint), 5, Scalar(0, 255, 0), -1); // 绿色点

    // 判断测试点是否在多边形中
    bool inside = isPointInPolygon(testPoint, polygon);
    cout << "Point (" << testPoint.x << ", " << testPoint.y << ") is "
         << (inside ? "inside" : "outside") << " the polygon." << endl;

    // 创建文字标注
    string status = inside ? "Inside the Polygon" : "Outside the Polygon";
    putText(image, status, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 0), 2);

    // 显示结果
    imshow("Polygon and Point", image);
    waitKey(0);

    return 0;
}
