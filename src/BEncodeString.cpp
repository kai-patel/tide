#include <BEncodeString.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/spirit/home/qi/directive/omit.hpp>
#include <boost/spirit/include/qi.hpp>

BOOST_FUSION_ADAPT_STRUCT(tide::BEncodeString, (std::string, contents))

namespace tide {

template <typename I>
struct string_parser : ::boost::spirit::qi::grammar<I, tide::BEncodeString> {
  ::boost::spirit::qi::rule<I, tide::BEncodeString> start;

  string_parser() : string_parser::base_type(start) {
    using ::boost::phoenix::ref;
    using ::boost::spirit::qi::_1;
    using ::boost::spirit::qi::char_;
    using ::boost::spirit::qi::omit;
    using ::boost::spirit::qi::repeat;
    using ::boost::spirit::qi::ulong_;

    unsigned long length;

    start %=
        (omit[ulong_[ref(length) = _1] >> ':'] >> repeat(ref(length))[char_]);
  }
};

bool BEncodeString::parse(std::string input) {
  auto first = input.cbegin();
  auto last = input.cend();

  bool r = boost::spirit::qi::parse(
      first, last, string_parser<std::string::const_iterator>(), *this);

  if (r == false || first != last) {
    return false;
  }

  return true;
}

} // namespace tide
