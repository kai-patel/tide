#pragma once

#include <BEncodeValue.hpp>
#include <map>

struct BEncodeDict : public BEncodeValue {
  std::map<BEncodeValue, BEncodeValue> contents;

  bool parse(std::string) override;
};
