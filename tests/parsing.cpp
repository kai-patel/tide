#include <gtest/gtest.h>
#include <tide.hpp>

TEST(Parsing, Integer) {
  std::string input = "i42e";

  tide::BEncodeValue result;

  result.parse(input);

  ASSERT_EQ(42, std::get<long>(result.value));
}

TEST(Parsing, String) {
  std::string input = "4:spam";

  tide::BEncodeValue result;

  result.parse(input);

  ASSERT_EQ("spam", std::get<std::string>(result.value));
}
