#include <BEncodeValue.hpp>

class BEncodeInteger : public BEncodeValue {
  long number = 0;

  void parse(std::string) override;
};
