add_library(libkvs kvs.cpp)
add_library(kvs::libkvs ALIAS libkvs)
set_target_properties(
    libkvs
    PROPERTIES
    OUTPUT_NAME kvs
)

target_include_directories(libkvs PUBLIC ${CMAKE_SOURCE_DIR}/include)
