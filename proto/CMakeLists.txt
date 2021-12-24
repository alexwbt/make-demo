add_library(proto)

find_package(Protobuf REQUIRED)

target_include_directories(
    proto PUBLIC .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

set(PROTO_SOURCES
    vec2.proto
)
protobuf_generate_cpp(LIB_SOURCES LIB_HEADERS ${PROTO_SOURCES})
target_link_libraries(proto ${Protobuf_LIBRARIES})

target_sources(proto
    PUBLIC ${LIB_HEADERS}
    PRIVATE ${LIB_SOURCES}
)
