cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Obstacle_Container)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # 显示代码警告
set(CMAKE_BUILD_TYPE Debug) # 设置Debug模式

# MATH(EXPR stack_size "500*1024*1024")
# set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
# set(CMAKE_PREFIX_PATH "/home/luanfuqiang/workSpace/Lib/opencv/x86_64_20/lib/cmake/opencv4")
#opencv
# find_package(OpenCV REQUIRED) #加这一句 
# include_directories(${OpenCV_INCLUDE_DIRS} ) #加这一句 
# include_directories(/home/luanfuqiang/workSpace/Lib/opencv/x86_64_20/include)
# include_directories(/usr/local/include/opencv4)
#pcl
# find_package(PCL 1.10 REQUIRED)
# PCL头文件路径
# include_directories(${PCL_INCLUDE_DIRS})
# 链接PCL库
# link_directories(${PCL_LIBRARY_DIRS})

# 加载头文件
include_directories(${CMAKE_SOURCE_DIR}/include ./include )
file(GLOB CPPFILES src/*.cpp src/*.h)
# 生成可执行文件
add_executable(Obstacle_Container main.cpp ${CPPFILES})
# 将可执行文件与PCL库进行连接
# target_link_libraries(Obstacle_Container ${OpenCV_LIBS} ${PCL_LIBRARIES})
# target_link_libraries(Obstacle_Container ${OpenCV_LIBS} /home/luanfuqiang/workSpace/Lib/opencv/x86_64_20/lib/)

# 链接 pthread 库
find_package(Threads REQUIRED)
target_link_libraries(Obstacle_Container PRIVATE Threads::Threads)



