#include <InfoDict.hpp>
#include <chrono>

class MetaInfo {
  InfoDict info;
  std::string announce;
  std::optional<std::vector<std::vector<std::string>>> announce_list;
  std::time_t creation_date;
  std::optional<std::string> comment;
  std::optional<std::string> created_by;
  std::optional<std::string> encoding;
};
