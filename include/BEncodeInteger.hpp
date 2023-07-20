#pragma once

#include <BEncodeValue.hpp>
#include <string>

namespace tide {

struct BEncodeInteger : public BEncodeValue {
  long number = 0;
  bool parse(std::string) override;
};

} // namespace tide
