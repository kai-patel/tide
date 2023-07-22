#include <BEncodeValue.hpp>

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/spirit/home/qi.hpp>
#include <map>
#include <string>
#include <variant>
#include <vector>

BOOST_FUSION_ADAPT_STRUCT(tide::BEncodeValue, (tide::any_type, value));
BOOST_FUSION_ADAPT_STRUCT(tide::BEncodeList,
                          (std::vector<tide::ListContents>, contents));

BOOST_FUSION_ADAPT_STRUCT(tide::BEncodeDict, (auto, dict));

namespace tide {

template <typename I>
struct dict_parser : boost::spirit::qi::grammar<I, BEncodeValue()> {
  boost::spirit::qi::rule<I, BEncodeValue()> start;
  boost::spirit::qi::rule<I, BEncodeInteger()> integer;
  boost::spirit::qi::rule<I, BEncodeString()> string;
  boost::spirit::qi::rule<I, BEncodeList()> list;
  boost::spirit::qi::rule<I, std::pair<DictKey, DictValue>()> pair;
  boost::spirit::qi::rule<I, BEncodeDict()> dict;

  int length;

  dict_parser() : dict_parser::base_type(start) {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    using ascii::char_;
    using boost::phoenix::ref;
    using qi::_1;
    using qi::byte_;
    using qi::inf;
    using qi::int_;
    using qi::long_;
    using qi::omit;
    using qi::repeat;

    integer %= ('i' >> long_ >> 'e');

    string %=
        (omit[(int_[ref(length) = _1] >> ':')] >> repeat(ref(length))[byte_]);

    list %= ('l' >> *(string | integer | list | dict) >> 'e');

    pair = (string >> (string | integer | list | dict));

    dict %= ('d' >> *(pair) >> 'e');

    start %= string | integer | list | dict;
  }
};

bool BEncodeValue::parse(std::string input) {
  auto first = input.cbegin();
  auto last = input.cend();

  bool result = boost::spirit::qi::parse(
      first, last, dict_parser<std::string::const_iterator>(), *this);

  if (result == false || first != last) {
    std::string rest(first, last);
    std::cerr << "Failed to parse at: <" << rest << ">" << std::endl;
    return false;
  }

  return true;
}

} // namespace tide
