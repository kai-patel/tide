# Find header files

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
# set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/tide.hpp")

message("Header list: ${HEADER_LIST}")

# Define IDE folder for headers
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

macro(add_auto_lib LIBNAME FILES INCLUDE)
  add_library(${LIBNAME} ${FILES} ${HEADER_LIST})

  # Public interface
  target_include_directories(${LIBNAME} PUBLIC ${INCLUDE})

  # Private dependency
  target_link_libraries(${LIBNAME} PRIVATE ${ARGN})

  # Optionally use target_compile_features() as well
endmacro()

# Use add_auto_lib() and add_executable() below here

# add_auto_lib(tide tide.cpp BEncodeInteger.cpp ../include Boost::boost)

add_library(tide ${SOURCE_LIST})

target_include_directories(tide PUBLIC ../include)

target_link_libraries(tide PRIVATE Boost::boost)
