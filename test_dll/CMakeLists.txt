cmake_minimum_required(VERSION 3.5)
project(test_fast_sort)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD_REQUIRED 20)
add_library(type
    Type.cpp
)
add_executable(main
    main.cpp
)
link_directories(
    # build
)
# target_include_directories(main
#     .
# )
target_link_libraries(main
    libtype.a
)