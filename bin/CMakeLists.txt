add_executable(bitcask main.cpp)
target_link_libraries(bitcask PRIVATE kvs::libkvs)
