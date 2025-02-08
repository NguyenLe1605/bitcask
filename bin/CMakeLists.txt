include(FetchContent)
FetchContent_Declare(
  cli11_proj
  QUIET
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.4.2)

FetchContent_MakeAvailable(cli11_proj)

add_executable(bitcask bitcask.cpp)
target_include_directories(bitcask PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(bitcask PRIVATE kvs::libkvs CLI11::CLI11)
