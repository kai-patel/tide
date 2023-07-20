#pragma once

#include <optional>
#include <string>
#include <vector>

class InfoFile {
  unsigned long length = 0;
  std::optional<std::string> md5sum;
  std::vector<std::string> path;
};
