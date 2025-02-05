find_package(GTest CONFIG REQUIRED)
add_executable(kvs_store_tests kvs_store_tests.cpp)
target_link_libraries(kvs_store_tests PRIVATE kvs::libkvs GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(kvs_store_tests)
