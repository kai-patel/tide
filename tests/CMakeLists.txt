macro(add_google_test TESTNAME LIBRARIES)
  # Define test target
  add_executable(${TESTNAME} ${ARGN})

  # Link test targets to GTest
  target_link_libraries(${TESTNAME} PRIVATE GTest::gtest_main ${LIBRARIES})

  gtest_discover_tests(${TESTNAME})
endmacro()

include(GoogleTest)

# Use add_google_test() below here

add_google_test(parsing "tide;Boost::boost" parsing.cpp)
