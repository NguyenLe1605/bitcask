cmake_minimum_required(VERSION 3.19)
project(
  "bitcask"
  LANGUAGES CXX
  VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

configure_file(config/version.h.in version.h @ONLY)

add_subdirectory("bin")
add_subdirectory("lib")

include(CTest)

if(BUILD_TESTING)
  add_subdirectory("tests")
endif()
