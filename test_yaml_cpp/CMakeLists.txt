cmake_minimum_required(VERSION 3.5)
project(test_yaml_cpp)
# set(CMAKE_CXX_STANDARD 11)
add_definitions(-std=c++11)
include_directories(
    /Users/haypin/Downloads/Repositories/yaml-cpp/include
)
link_directories(
    /Users/haypin/Downloads/Repositories/yaml-cpp/build
)
add_executable(main test_yaml_cpp.cpp)
target_link_libraries(
    main
    libyaml-cpp.a
)