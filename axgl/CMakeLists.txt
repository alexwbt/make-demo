
add_library(axgl)

target_sources(axgl
    PRIVATE
    ./src/window.cpp
    ./src/gameloop.cpp
)

target_include_directories(axgl
    PRIVATE
    glfw/include
    glad/include
    PUBLIC
    ./include
)

target_link_libraries(axgl
    PRIVATE
    glfw
    glad
)
