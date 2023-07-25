#include <InfoFile.hpp>
#include <exception>

namespace tide {

class InfoFileException : public std::exception {
  const char *what() { return "Malformed File Info in input"; }
};

InfoFile::InfoFile(ListContents &dict) {
  auto input = std::get<BEncodeDict>(dict).dict;

  if (input.find("length") != input.end()) {
    length = std::get<BEncodeInteger>(input["length"]);
  } else {
    throw InfoFileException();
  }

  if (input.find("md5sum") != input.end()) {
    md5sum = std::get<BEncodeString>(input["md5sum"]);
  }

  if (input.find("path") != input.end()) {
    auto path_list = std::get<BEncodeList>(input["path"]).contents;
    for (int i = 0; i < path_list.size(); i++) {
      path.push_back(std::get<BEncodeString>(path_list[i]));
    }
  } else {
    throw InfoFileException();
  }
}

} // namespace tide
