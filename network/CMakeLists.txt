
add_library(net)

target_sources(net
    PRIVATE
    ./src/connection.cpp
    ./src/client.cpp
    ./src/server.cpp
)

target_include_directories(net
    PUBLIC
    ../external/asio/asio/include
    ./include
)

target_link_libraries(net
    PUBLIC
    proto
)
