#pragma once

#include "BEncodeValue.hpp"
#include <optional>
#include <string>
#include <vector>

namespace tide {

class InfoFile {
public:
  unsigned long length = 0;
  std::optional<std::string> md5sum;
  std::vector<std::string> path;

  InfoFile(ListContents &);
};

} // namespace tide
