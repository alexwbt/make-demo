
add_library(axgl)

target_sources(axgl
    PRIVATE
    ./src/window.cpp
)

target_include_directories(axgl
    PRIVATE
    glfw/include
    PUBLIC
    ./include
)

target_link_libraries(axgl
    PRIVATE
    glfw
)
