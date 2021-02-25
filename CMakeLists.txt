cmake_minimum_required(VERSION 3.14)
project(SORA)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(./thirdparty/glm-master)

add_executable(SORA main.cpp rasterizer.cpp cube.cpp vertex.cpp triangle.cpp utilities.cpp)
target_link_libraries(SORA ${OpenCV_LIBS})