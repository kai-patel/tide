#include <BEncodeValue.hpp>
#include <vector>

class BEncodeList : public BEncodeValue {
  std::vector<BEncodeValue> elements;

  void parse(std::string) override;
};
