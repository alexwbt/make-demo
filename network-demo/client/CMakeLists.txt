
add_executable(net_demo_client)

target_sources(net_demo_client
    PRIVATE
    ./src/main.cpp
)

target_link_libraries(net_demo_client
    PRIVATE
    net
)
