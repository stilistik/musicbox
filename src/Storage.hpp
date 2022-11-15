#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include <SD.h>
#include <MTP_Teensy.h>
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
  std::vector<std::shared_ptr<Track>> tracks;
  std::vector<std::shared_ptr<Album>> albums;
  void read_files();
  std::shared_ptr<Album> get_album_with_name(std::string n);
  bool setup_successful = false;

public:
  Storage();
  void setup();
  void update();
};

#endif /* STORAGE_HPP_ */
