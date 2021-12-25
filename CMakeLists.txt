cmake_minimum_required(VERSION 3.22)

# project
project(make_demo VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/_bin)

# DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# subdirectories
add_subdirectory(proto)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# main executable
set(SRC_DIR ./src)
set(MAIN_SOURCES
    ${SRC_DIR}/main.cpp
)
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/glad/include
    PUBLIC external/glm
    PUBLIC external/stb
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE proto
    PRIVATE glfw
    PRIVATE glad
)
