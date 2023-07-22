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

  dict_parser() : dict_parser::base_type(start) {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    using ascii::char_;
    using boost::phoenix::ref;
    using qi::_1;
    using qi::long_;
    using qi::omit;
    using qi::repeat;
    using qi::ulong_;

    integer %= ('i' >> long_ >> 'e');

    unsigned long length;

    string %=
        (omit[ulong_[ref(length) = _1] >> ':'] >> repeat(ref(length))[char_]);

    list %= ('l' >> *(integer | string | list) >> 'e');

    pair %= (string >> (integer | string | list | dict));

    dict %= ('d' >> *(pair) >> 'e');

    start %= integer | string | list;
  }
};

bool BEncodeValue::parse(std::string input) {
  auto first = input.cbegin();
  auto last = input.cend();

  bool result = boost::spirit::qi::parse(
      first, last, dict_parser<std::string::const_iterator>(), *this);

  if (result == false || first != last) {
    return false;
  }

  return true;
}

} // namespace tide
