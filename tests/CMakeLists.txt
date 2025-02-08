# include modules
include(FetchContent)
FetchContent_Declare(
  reproc
  GIT_REPOSITORY https://github.com/DaanDeMeyer/reproc.git
  GIT_TAG v14.2.5)

set(REPROC++ ON)
FetchContent_MakeAvailable(reproc)

find_package(GTest CONFIG REQUIRED)

# create the testing libraries
add_executable(kvs_store_tests kvs_store_tests.cpp)
target_link_libraries(kvs_store_tests PRIVATE kvs::libkvs GTest::gtest_main)

add_executable(kvs_cli_tests kvs_cli_tests.cpp)
target_link_libraries(kvs_cli_tests PRIVATE reproc++ GTest::gtest_main)
target_include_directories(kvs_cli_tests PRIVATE ${CMAKE_BINARY_DIR})

include(GoogleTest)
gtest_discover_tests(kvs_store_tests)
gtest_discover_tests(kvs_cli_tests)
