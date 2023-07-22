#pragma once

#include <boost/any.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace tide {
typedef long BEncodeInteger;
typedef std::string BEncodeString;

struct BEncodeList;
struct BEncodeDict;

typedef std::variant<BEncodeInteger, BEncodeString,
                     boost::recursive_wrapper<BEncodeList>, BEncodeDict>
    ListContents;

struct BEncodeList {
  std::vector<ListContents> contents;
};

typedef BEncodeString DictKey;
typedef std::variant<BEncodeInteger, BEncodeString, BEncodeList,
                     boost::recursive_wrapper<BEncodeDict>>
    DictValue;

struct BEncodeDict {
  std::map<DictKey, DictValue> dict;
};

typedef std::variant<BEncodeInteger, BEncodeString, BEncodeList, BEncodeDict> any_type;

struct BEncodeValue {
  any_type value;

  bool parse(std::string);
};

} // namespace tide
