set(PROTO_LIB proto)
add_library(${PROTO_LIB})

find_package(Protobuf REQUIRED)

# generate proto
set(PROTO_SOURCES
    vec2.proto
)
protobuf_generate_cpp(LIB_SOURCES LIB_HEADERS ${PROTO_SOURCES})

# includes
target_include_directories(${PROTO_LIB}
    PUBLIC .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
)

# links
target_link_libraries(${PROTO_LIB}
    ${Protobuf_LIBRARIES}
)

# sources
target_sources(${PROTO_LIB}
    PUBLIC ${LIB_HEADERS}
    PRIVATE ${LIB_SOURCES}
)
