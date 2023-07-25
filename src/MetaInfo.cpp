#include "BEncodeValue.hpp"
#include "InfoDict.hpp"
#include <MetaInfo.hpp>
#include <exception>

namespace tide {

class MetaInfoException : public std::exception {
  const char *what() { return "Malformed MetaInfo input"; }
};

MetaInfo::MetaInfo(std::string &input) {
  BEncodeValue result;

  bool is_parsed = result.parse(input);

  if (!is_parsed) {
    throw MetaInfoException();
  }

  std::map<DictKey, DictValue> dict = std::get<BEncodeDict>(result.value).dict;

  if (dict.find("announce") != dict.end()) {
    announce = std::get<BEncodeString>(dict["announce"]);
  } else {
    throw MetaInfoException();
  }

  if (dict.find("comment") != dict.end()) {
    comment = std::get<BEncodeString>(dict["comment"]);
  }

  if (dict.find("created_by") != dict.end()) {
    created_by = std::get<BEncodeString>(dict["created_by"]);
  }

  if (dict.find("encoding") != dict.end()) {
    encoding = std::get<BEncodeString>(dict["encoding"]);
  }

  if (dict.find("info") != dict.end()) {
    std::map<DictKey, DictValue> info_dict =
        std::get<boost::recursive_wrapper<BEncodeDict>>(dict["info"])
            .get()
            .dict;

    if (info_dict.find("length") != info_dict.end()) {
      // Multi-file
      info = MultiFileInfoDict(info_dict);
    } else {
      // Single-file
      info = SingleFileInfoDict(info_dict);
    }

  } else {
    throw MetaInfoException();
  }

  if (dict.find("announce_list") != dict.end()) {
    // TODO http://bittorrent.org/beps/bep_0012.html
    /* announce_list = std::get<BEncodeList>(dict["announce_list"]); */
  }
}

} // namespace tide
