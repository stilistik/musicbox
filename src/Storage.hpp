#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include <SD.h>
#include <MTP_Teensy.h>
#include <vector>
#include <map>
#include <string>
#include <memory>

#define SD_SLOT BUILTIN_SDCARD
#define DELIMITER "__"

class Storage
{
private:
  std::map<std::string, std::vector<std::string>> content;
  void read_files();
  bool setup_successful = false;

public:
  Storage();
  void setup();
  void update();
};

#endif /* STORAGE_HPP_ */
