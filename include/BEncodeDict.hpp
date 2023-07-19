#include <BEncodeValue.hpp>
#include <map>

class BEncodeDict : public BEncodeValue {
  std::map<BEncodeValue, BEncodeValue> contents;

  void parse(std::string) override;
};
