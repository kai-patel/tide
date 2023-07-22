#include <boost/any.hpp>
#include <gtest/gtest.h>
#include <tide.hpp>

TEST(Parsing, Integer) {
  std::string input = "i42e";

  tide::BEncodeValue result;

  result.parse(input);

  ASSERT_EQ(42, std::get<tide::BEncodeInteger>(result.value));
}

TEST(Parsing, String) {
  std::string input = "4:spam";

  tide::BEncodeValue result;

  result.parse(input);

  ASSERT_EQ("spam", std::get<tide::BEncodeString>(result.value));
}

TEST(Parsing, List) {
  std::string input = "l4:spami42ee";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  ASSERT_EQ(true, is_parsed);

  auto actual = std::get<tide::BEncodeList>(result.value).contents;

  EXPECT_EQ("spam", std::get<tide::BEncodeString>(actual[0]));
  EXPECT_EQ(42, std::get<tide::BEncodeInteger>(actual[1]));
}
