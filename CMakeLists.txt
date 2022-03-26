# cmake学习：https://www.jianshu.com/p/2b6cbf53ba95
cmake_minimum_required(VERSION 3.10.2)

# 项目信息
project (lh_trans)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=gnu++11") #-std=c++11
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# add_definitions(-DRTMPDUMP_VERSION="v2.4")
#程序名字
set(prg01_name send264)
# 程序文件变量
set(prg01_inc_dir PUBLIC)
set(prg01_src)


# 必须手动将链接的库安装到指定路径，否则报一下错误
# error while loading shared libraries: libjsoncpp.so.25: cannot open shared object file: No such file or directory
link_directories("/usr/local/lib")

# 编译动态 lib 库
add_executable(${prg01_name} librtmp_send264.cpp  simplest_librtmp_send264.cpp )    

target_link_directories(${prg01_name} PUBLIC lib)
target_link_libraries(${prg01_name} pthread ssl crypto zlog jsoncpp rtmp)   
target_include_directories(${prg01_name} PUBLIC include)