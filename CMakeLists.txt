
cmake_minimum_required(VERSION 2.8.1)

project (server)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

aux_source_directory(.  SRC_LIST)
include_directories(${CMAKE_CURRENT_LIST_DIR}/libevent/include)
include_directories(${CMAKE_CURRENT_LIST_DIR} )
include_directories(${CMAKE_CURRENT_LIST_DIR}/jsoncpp/)

message(" CMAKE_CURRENT_LIST_DIR =  ${CMAKE_CURRENT_LIST_DIR} ")
add_executable (hello_bin ${SRC_LIST})
 
# 添加链接库
target_link_libraries(hello_bin event jsoncpp)
 