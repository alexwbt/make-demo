cmake_minimum_required(VERSION 3.22)

project(MakeDemo VERSION 0.1 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_bin)

add_subdirectory(proto)

set(SRC ./src)
add_executable(make_demo ${SRC}/main.cpp)
target_link_libraries(make_demo PUBLIC proto)
