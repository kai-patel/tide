#include <BEncodeInteger.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/spirit/include/qi.hpp>

BOOST_FUSION_ADAPT_STRUCT(tide::BEncodeInteger, (long, number));

namespace tide {

template <typename I>
struct integer_parser : ::boost::spirit::qi::grammar<I, tide::BEncodeInteger> {
  ::boost::spirit::qi::rule<I, tide::BEncodeInteger> start;

  integer_parser() : integer_parser::base_type(start) {
    using ::boost::phoenix::ref;
    using ::boost::spirit::qi::_1;
    using ::boost::spirit::qi::long_;
    start %= ('i' >> long_ >> 'e');
  }
};

bool BEncodeInteger::parse(std::string input) {
  auto first = input.cbegin();
  auto last = input.cend();

  bool r = boost::spirit::qi::parse(
      first, last, integer_parser<std::string::const_iterator>(), *this);

  if (r == false || first != last) {
    return false;
  }

  return true;
}

} // namespace tide
