#pragma once

#include "BEncodeValue.hpp"
#include <InfoFile.hpp>

namespace tide {

class InfoDict {
  unsigned int piece_length = 0;
  std::string pieces;
  std::optional<bool> is_private;
};

class SingleFileInfoDict : public InfoDict {
public:
  std::string name;
  unsigned long length = 0;
  std::optional<std::string> md5sum;
  SingleFileInfoDict(std::map<DictKey, DictValue> &);
};

class MultiFileInfoDict : public InfoDict {
public:
  std::string name;
  std::vector<InfoFile> files;

  MultiFileInfoDict(std::map<DictKey, DictValue> &);
};

} // namespace tide
