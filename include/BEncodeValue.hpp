#pragma once

#include <boost/any.hpp>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace tide {
typedef std::variant<long, std::string, std::vector<boost::any>> any_type;

struct BEncodeValue {
  any_type value;

  bool parse(std::string);
};

} // namespace tide
