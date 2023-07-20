#pragma once

#include <BEncodeValue.hpp>

namespace tide {

struct BEncodeString : public BEncodeValue {
  std::string contents;
  bool parse(std::string) override;
};

} // namespace
