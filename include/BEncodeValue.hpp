#pragma once

#include <string>

struct BEncodeValue {
  virtual bool parse(std::string) = 0;
};
