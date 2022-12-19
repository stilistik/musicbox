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
#define DELIMITER "__"

class Storage
{
private:
  int current_album_index = 0;
  std::vector<std::shared_ptr<Track>> tracks;
  std::vector<std::shared_ptr<Album>> albums;
  std::shared_ptr<Album> get_album_with_name(std::string n);
  bool setup_successful = false;
  void read_index();
  void restore_index_from_backup();

public:
  Storage();
  void setup();
  void update();
  std::shared_ptr<Album> get_album(int idx);
  std::shared_ptr<Track> get_track_by_rfid(std::string rfid);
  void write_track_rfid(std::string rfid, std::shared_ptr<Track> t);
  int get_album_index(std::shared_ptr<Album> album);
  int get_album_count();
  std::shared_ptr<Album> get_next_album();
  std::shared_ptr<Album> get_current_album();
  std::shared_ptr<Track> get_current_track();
  std::shared_ptr<Track> get_next_track();
  std::shared_ptr<Track> get_prev_track();
};

#endif /* STORAGE_HPP_ */
