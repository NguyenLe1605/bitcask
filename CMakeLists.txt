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

set(BITCASK_SCRIPT_DIR ${CMAKE_SOURCE_DIR}/scripts)

# clang-related tools, Modified from Bustub
set(BITCASK_CLANG_SEARCH_PATH
    "/usr/local/bin" "/usr/bin" "/usr/local/opt/llvm/bin"
    "/usr/local/opt/llvm@14/bin" "/opt/homebrew/opt/llvm@14/bin/")

# clang-format -

# attempt to find the binary if user did not specify
find_program(
  CLANG_FORMAT_BIN
  NAMES clang-format clang-format-14
  HINTS ${BITCASK_CLANG_SEARCH_PATH})

if("${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
  message(WARNING "bitcask couldn't find clang-format.")
else()
  message(STATUS "bitcask found clang-format at ${CLANG_FORMAT_BIN}")
endif()

# ##############################################################################
# MAKE TARGETS
# ##############################################################################

# ##############################################################################
# "make format"
# ##############################################################################
string(
  CONCAT BITCASK_FORMAT_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/bin,"
         "${CMAKE_CURRENT_SOURCE_DIR}/test," "${CMAKE_CURRENT_SOURCE_DIR}/lib,"
         "${CMAKE_CURRENT_SOURCE_DIR}/include,")

# Runs clang format and updates files in place.
add_custom_target(
  format
  ${BITCASK_SCRIPT_DIR}/run_clang_format.py
  ${CLANG_FORMAT_BIN}
  ${BITCASK_SCRIPT_DIR}/clang_format_exclusions.txt
  --source_dirs
  ${BITCASK_FORMAT_DIRS}
  --fix
  --quiet)
