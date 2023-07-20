#pragma once

#include <InfoFile.hpp>

class InfoDict {
  unsigned int piece_length = 0;
  std::string pieces;
  std::optional<bool> is_private;
};

class SingleFileInfoDict : public InfoDict {
  std::string name;
  unsigned long length = 0;
  std::optional<std::string> md5sum;
};

class MultiFileInfoDict : public InfoDict {
  std::string name;
  std::vector<InfoFile>;
};
