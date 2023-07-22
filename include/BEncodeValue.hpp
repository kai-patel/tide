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

typedef std::variant<BEncodeInteger, BEncodeString,
                     boost::recursive_wrapper<BEncodeList>>
    ListContents;

struct BEncodeList {
  std::vector<ListContents> contents;
};

struct BEncodeDict;

typedef std::variant<BEncodeInteger, BEncodeString, BEncodeList,
                     boost::recursive_wrapper<BEncodeDict>>
    DictValue;

typedef BEncodeString DictKey;

struct BEncodeDict {
  std::map<DictKey, DictValue> contents;
};

typedef std::variant<BEncodeInteger, BEncodeString, BEncodeList> any_type;

struct BEncodeValue {
  any_type value;

  bool parse(std::string);
};

} // namespace tide
