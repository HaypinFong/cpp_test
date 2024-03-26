cmake_minimum_required(VERSION 3.5)
project(test_boost_signals2)
message(STATUS "$<CMAKE_MODULE_PATH>: ${CMAKE_MODULE_PATH}")
find_package(Boost REQUIRED COMPONENTS thread system)
message(STATUS "$<Boost_LIBRARIES>: ${Boost_LIBRARIES}")
include_directories(
    /usr/local/Cellar/boost/1.76.0/include
)
link_directories(
    /usr/local/Cellar/boost/1.76.0/lib
)
add_executable(
    main
    main.cpp
)

target_link_libraries(
    main
    ${Boost_LIBRARIES} boost_system boost_thread
    # boost_system 
    # boost_thread
)