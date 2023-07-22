# Set CMake Version
cmake_minimum_required(VERSION 3.24)

# Define Project
project(
  Tide
  VERSION 0.1
  DESCRIPTION ""
  LANGUAGES CXX)

# Set CMAKE_ variables

set(CMAKE_MODULE_PATH, "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set language standards
set(CMAKE_CXX_STANDARD 17)

# Disable standards extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# Support IDE folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Declare options
option(BUILD_TESTS "Enable/disable test building" ON)

# Clang-Tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND ${CLANG_TIDY_EXE} "--checks=-*,modernize-*")

# Find packages

# Google Test
if(BUILD_TESTS)
  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0)

  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)

  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  endif()

  FetchContent_MakeAvailable(googletest)
  enable_testing()
endif(BUILD_TESTS)

# Doxygen
find_package(Doxygen)
if(Doxygen_FOUND)
  add_subdirectory(docs)
else()
  message(STATUS "Could not find Doxygen, not building docs/")
endif()

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.82 REQUIRED)

# Fix IMPORT targets if our CMake is older than Boost CMake

if(NOT TARGET Boost::boost)
  add_library(Boost::boost IMPORTED INTERFACE)
  set_property(TARGET Boost::boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                                            ${Boost_INCLUDE_DIR})
  set_property(TARGET Boost::boost PROPERTY INTERFACE_LINK_LIBRARIES
                                            ${Boost_LIBRARIES})
endif()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(examples)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(
    FATAL_ERROR
      "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles."
  )
endif()
