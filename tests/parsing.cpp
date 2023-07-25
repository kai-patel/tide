#include "BEncodeValue.hpp"
#include <boost/any.hpp>
#include <gtest/gtest.h>
#include <tide.hpp>

TEST(Parsing, Integer) {
  std::string input = "i42e";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  ASSERT_EQ(true, is_parsed);

  ASSERT_EQ(42, std::get<tide::BEncodeInteger>(result.value));
}

TEST(Parsing, String) {
  std::string input = "4:spam";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  ASSERT_EQ(true, is_parsed);

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

TEST(Parsing, ListofLists) {
  std::string input = "l4:spaml3:hami42eei101ee";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  auto actual = std::get<tide::BEncodeList>(result.value).contents;

  EXPECT_EQ("spam", std::get<tide::BEncodeString>(actual[0]));

  auto inner_list =
      std::get<boost::recursive_wrapper<tide::BEncodeList>>(actual[1]);

  EXPECT_EQ("ham", std::get<tide::BEncodeString>(inner_list.get().contents[0]));
  EXPECT_EQ(42, std::get<tide::BEncodeInteger>(inner_list.get().contents[1]));

  EXPECT_EQ(101, std::get<tide::BEncodeInteger>(actual[2]));
}

TEST(Parsing, ListofDict) {
  std::string input = "ld3:fooi42ee5:helloe";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  ASSERT_EQ(true, is_parsed);

  auto actual = std::get<tide::BEncodeList>(result.value).contents;
  auto dict = std::get<tide::BEncodeDict>(actual[0]).dict;

  EXPECT_EQ(42, std::get<tide::BEncodeInteger>(dict["foo"]));
  EXPECT_EQ("hello", std::get<tide::BEncodeString>(actual[1]));
}

TEST(Parsing, Dictionary) {
  std::string input = "d3:bar4:spam3:fooi42ee";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  ASSERT_EQ(true, is_parsed);

  auto actual = std::get<tide::BEncodeDict>(result.value).dict;

  EXPECT_EQ("spam", std::get<tide::BEncodeString>(actual["bar"]));
  EXPECT_EQ(42, std::get<tide::BEncodeInteger>(actual["foo"]));
}

TEST(Parsing, DictofDict) {
  std::string input = "d3:bard3:fooi42eee";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  ASSERT_EQ(true, is_parsed);

  auto actual = std::get<tide::BEncodeDict>(result.value).dict;
  tide::BEncodeDict value =
      std::get<boost::recursive_wrapper<tide::BEncodeDict>>(actual["bar"])
          .get();

  auto inner = value.dict;

  EXPECT_EQ(42, std::get<tide::BEncodeInteger>(inner["foo"]));
}

TEST(Parsing, DictofList) {
  std::string input = "d3:fool3:bar3:bazee";

  tide::BEncodeValue result;

  bool is_parsed = result.parse(input);

  ASSERT_EQ(true, is_parsed);

  auto dict = std::get<tide::BEncodeDict>(result.value).dict;

  auto list = std::get<tide::BEncodeList>(dict["foo"]).contents;

  ASSERT_EQ("bar", std::get<tide::BEncodeString>(list[0]));
  ASSERT_EQ("baz", std::get<tide::BEncodeString>(list[1]));
}
