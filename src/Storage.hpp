#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include <SD.h>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Track.hpp"
#include "Album.hpp"

#define SD_SLOT BUILTIN_SDCARD

class Storage
{
private:
  std::vector<std::shared_ptr<Track>> tracks;
  std::vector<std::shared_ptr<Album>> albums;
  std::vector<std::string> index_content;
  std::shared_ptr<Album> get_album_with_name(std::string n);
  bool setup_successful = false;
  void read_index();
  void restore_index_from_backup();

public:
  Storage();
  void setup();
  void update();
  std::shared_ptr<Track> get_track_by_rfid(std::string rfid);
  void write_track_rfid(std::string rfid, std::shared_ptr<Track> t);
  std::shared_ptr<Album> get_next_album(std::shared_ptr<Album> current_album);
};

#endif /* STORAGE_HPP_ */
