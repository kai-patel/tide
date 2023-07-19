#include <boost/asio.hpp>
#include <optional>
#include <string>
#include <vector>

class Torrent {
  unsigned int peers = 0;
  unsigned int pieces = 0;
};

class InfoFile {
  unsigned long length = 0;
  std::optional<std::string> md5sum;
  std::vector<std::string> path;
};

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

class MetaInfo {
  InfoDict info;
  std::string announce;
  std::optional<std::vector<std::vector<std::string>>> announce_list;
  std::time_t creation_date;
  std::optional<std::string> comment;
  std::optional<std::string> created_by;
  std::optional<std::string> encoding;
};
