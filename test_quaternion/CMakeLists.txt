cmake_minimum_required(VERSION 3.5)
project(test_quaternion)
set(CMAKE_CXX_STANDARD 11)
add_executable(main test_quaternion.cpp)
# find_package(
#     boost required
# )
include_directories(
    "/opt/ros/kinetic/include"
)