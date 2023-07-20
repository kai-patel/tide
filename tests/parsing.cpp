#include <gtest/gtest.h>
#include <tide.hpp>

TEST(Parsing, Integer) {
  std::string input = "i42e";

  tide::BEncodeInteger result;

  result.parse(input);

  ASSERT_EQ(42, result.number);
}

TEST(Parsing, String) {
  std::string input = "4:spam";

  tide::BEncodeString result;

  result.parse(input);

  ASSERT_EQ("spam", result.contents);
}
