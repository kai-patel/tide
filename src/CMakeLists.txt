# Find header files
file(GLOB HEADER_LIST "${CMAKE_SOURCE_DIR}/include/*.hpp")

# Define IDE folder for headers
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

macro(add_auto_lib LIBNAME FILES INCLUDE DEPS)
  add_library(${LIBNAME} ${FILES} ${HEADER_LIST})

  # Public interface
  target_include_directories(${LIBNAME} PUBLIC ${INCLUDE})

  # Private dependency
  target_link_libraries(${LIBNAME} PRIVATE ${DEPS})

  # Optionally use target_compile_features() as well
endmacro()

# Use add_auto_lib() and add_executable() below here
