#pragma once

#include <BEncodeValue.hpp>
#include <vector>

struct BEncodeList : public BEncodeValue {
  std::vector<BEncodeValue> elements;
};
