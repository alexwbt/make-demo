
add_executable(playground)

target_sources(playground
    PRIVATE
    src/main.cpp
)

target_link_libraries(playground
    PRIVATE
    axgl
)
