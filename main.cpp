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

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class SharedResource
{
private:
    mutable std::mutex mutex_; // 互斥锁
    int shared_data_;          // 共享资源

public:
    SharedResource() : shared_data_(0) {}

    void increment()
    {
        // 使用 std::lock_guard 加锁
        std::lock_guard<std::mutex> lock(mutex_);

        // 临界区：对共享数据进行操作
        shared_data_++;
        std::cout << "Shared data incremented to: " << shared_data_ << " by thread " << std::this_thread::get_id() << std::endl;
    }

    int getData()
    {
        // 使用 std::lock_guard 加锁，确保线程安全
        std::lock_guard<std::mutex> lock(mutex_);
        return shared_data_;
    }
};

int main()
{
    SharedResource resource;

    // 创建多个线程，并对共享资源执行操作
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back([&resource]()
                             { resource.increment(); });
    }

    // 等待线程完成
    for (auto &t : threads)
    {
        t.join();
    }

    std::cout << "Final shared data: " << resource.getData() << std::endl;

    return 0;
}
