#include "Track.hpp"

Track::Track(std::string name, std::string fp, std::string rfid) : name(name), file_path(fp), rfid(rfid) {}

const char *Track::get_file_path()
{
  return file_path.c_str();
}

std::string Track::get_rfid()
{
  return rfid;
}