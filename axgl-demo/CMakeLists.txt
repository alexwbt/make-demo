
add_executable(axgl_demo)

target_sources(axgl_demo
    PRIVATE
    src/main.cpp
)

target_link_libraries(axgl_demo
    PRIVATE
    axgl
)
