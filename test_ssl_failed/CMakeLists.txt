cmake_minimum_required(VERSION 3.5)
project(untitled_3)

set(CMAKE_CXX_STANDARD 11)
set(INC_DIR 
    /Users/haypin/Downloads/Repositories/openssl/include    # mac
    /home/haypin/Downloads/openssl/include                  # ubt
)
set(LINK_DIR 
    /Users/haypin/Downloads/Repositories/openssl            # mac
    /home/haypin/Downloads/openssl                          # ubt
)

include_directories(${INC_DIR})
include_directories(
        /Users/haypin/catkin_ws/src/beginner_tutorials/test_ssl
        /Users/haypin/Downloads/Repositories/openssl/include
        /Users/haypin/Downloads/Repositories/openssl

        /media/psf/Home/catkin_ws/src/beginner_tutorials/test_ssl
        /home/haypin/Downloads/openssl/include              # ubt
        /home/haypin/Downloads/openssl                      # ubt
)
link_directories(${LINK_DIR})
link_libraries(ssl crypto)


add_executable(untitled_3 main.cpp common_tool.cpp common_tool.h
        Base64.cpp
        Base64.h)
# target_link_libraries(untitled_3 openssl)
