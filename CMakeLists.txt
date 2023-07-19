# Set CMake Version
cmake_minimum_required(VERSION 3.24)

# Define Project
project(
  ProjectName
  VERSION 0.1
  DESCRIPTION ""
  LANGUAGES CXX)

# Set CMAKE_ variables

# Set language standards
set(CMAKE_CXX_STANDARD 14)

# Disable standards extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# Support IDE folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Declare options
option(BUILD_TESTS "Enable/disable test building" ON)

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
  FetchContent_MakeAvailable(googletest)
  enable_testing()
endif()

# Doxygen
find_package(Doxygen)
if(Doxygen_FOUND)
  add_subdirectory(docs)
else()
  message(STATUS "Could not find Doxygen, not building docs/")
endif()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(examples)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
