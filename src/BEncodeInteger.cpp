#include <BEncodeInteger.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/spirit/include/qi.hpp>

namespace tide {

bool BEncodeInteger::parse(std::string input) {
  using boost::phoenix::ref;
  using boost::spirit::qi::_1;
  using boost::spirit::qi::long_;
  using boost::spirit::qi::phrase_parse;
  using boost::spirit::qi::ascii::space;

  auto first = input.begin();
  auto last = input.end();

  bool result = phrase_parse(
      first, last, ('i' >> long_[ref(this->number) = _1] >> 'e'), space);

  if (result == false || first != last) {
    return false;
  }

  return result;
}

} // namespace tide
