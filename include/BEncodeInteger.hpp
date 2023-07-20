#pragma once

#include <BEncodeValue.hpp>
#include <string>

namespace tide {

struct BEncodeInteger : public BEncodeValue {
  long number = 0;
  void parse(std::string);
};

} // namespace tide
