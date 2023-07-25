#include "BEncodeValue.hpp"
#include <InfoDict.hpp>

namespace tide {

class InfoDictException : public std::exception {
  const char *what() { return "Malformed Info Dictionary in input"; }
};

InfoDict::InfoDict(std::map<DictKey, DictValue> &dict) {
  if (dict.find("piece length") != dict.end()) {
    piece_length = std::get<BEncodeInteger>(dict["piece length"]);
  } else {
    throw InfoDictException();
  }

  if (dict.find("pieces") != dict.end()) {
    pieces = std::get<BEncodeString>(dict["pieces"]);
  } else {
    throw InfoDictException();
  }

  if (dict.find("private") != dict.end()) {
    long private_int = std::get<BEncodeInteger>(dict["private"]);

    if (private_int == 1) {
      is_private = true;
    } else {
      is_private = false;
    }
  }
}

SingleFileInfoDict::SingleFileInfoDict(std::map<DictKey, DictValue> &dict)
    : InfoDict(dict) {
  if (dict.find("name") != dict.end()) {
    name = std::get<BEncodeString>(dict["name"]);
  } else {
    throw InfoDictException();
  }

  if (dict.find("length") != dict.end()) {
    length = std::get<BEncodeInteger>(dict["length"]);
  } else {
    throw InfoDictException();
  }

  if (dict.find("md5sum") != dict.end()) {
    md5sum = std::get<BEncodeString>(dict["md5sum"]);
  }
}

MultiFileInfoDict::MultiFileInfoDict(std::map<DictKey, DictValue> &dict)
    : InfoDict(dict) {
  if (dict.find("name") != dict.end()) {
    name = std::get<BEncodeString>(dict["name"]);
  } else {
    throw InfoDictException();
  }

  if (dict.find("files") != dict.end()) {
    std::vector<ListContents> files_list =
        std::get<BEncodeList>(dict["files"]).contents;
    for (int i = 0; i < files_list.size(); i++) {
      files.push_back(InfoFile(files_list[i]));
    }
  } else {
    throw InfoDictException();
  }
}

} // namespace tide
