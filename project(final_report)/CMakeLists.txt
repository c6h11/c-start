project(demo_1)
SET(CMAKE_CXX_COMPILER "g++")
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -march=native -O3 -pthread" )# 允许c++11标准、O3优化、多线程。match选项可避免一些cpu上的问题

find_package(Boost REQUIRED COMPONENTS
        serialization
        )

if(NOT Boost_FOUND)
    message("Boost NOT Found!")
else()
    message(STATUS "Boost Found!")
endif()

include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")


aux_source_directory(. SRC_LIST) # 搜索当前目录下的所有.cpp文件
add_executable(demo_1 ${SRC_LIST} mutex.h)
target_include_directories(demo_1 PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(demo_1 ${Boost_LIBRARIES})