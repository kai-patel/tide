#pragma once

#include <BEncodeValue.hpp>

struct BEncodeString : public BEncodeValue {
  std::string contents;
};
