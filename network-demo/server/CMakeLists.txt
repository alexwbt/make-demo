
add_executable(net_demo_server)

target_sources(net_demo_server
    PRIVATE
    ./src/main.cpp
)

target_link_libraries(net_demo_server
    PRIVATE
    net
)
