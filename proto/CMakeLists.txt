
add_library(proto)

find_package(Protobuf REQUIRED)

# generate protobuf
protobuf_generate_cpp(LIB_SOURCES LIB_HEADERS
    src/string_message.proto
)

target_sources(proto
    PUBLIC
    ${LIB_HEADERS}
    PRIVATE
    ${LIB_SOURCES}
)

target_include_directories(proto
    PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

target_link_libraries(proto
    PRIVATE
    ${Protobuf_LIBRARIES}
)
