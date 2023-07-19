#include <BEncodeValue.hpp>

class BEncodeString : public BEncodeValue {
  std::string contents;

  void parse(std::string) override;
};
