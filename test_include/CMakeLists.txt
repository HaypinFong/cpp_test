project(test_include)
cmake_minimum_required(VERSION 3.21)
add_executable(main 
    main.cpp 
    head1.cpp
    head2.cpp
    headmid.cpp
    mid.cpp
    #[[ [ 75%] Linking CXX executable main
    duplicate symbol 'Test::stcstr' in:
        CMakeFiles/main.dir/head1.cpp.o
        CMakeFiles/main.dir/head2.cpp.o
    # 源文件->xxx.o、xxx.a、xxx.so限定了名字查找的范围，范围内全局作用域不可名字重复 ]]#

    #[[ duplicate symbol 'func21()' in:
    CMakeFiles/main.dir/head2.cpp.o
    CMakeFiles/main.dir/mid.cpp.o
    重复的符号报错是单独的xxx.cpp.o各自链接到的其他xxx.cpp.o满足名字唯一，但add_executable
    或add_library构建可执行程序时“导出”的符号不唯一，所以不能生成
    ]]#
)