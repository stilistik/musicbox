#include "Track.hpp"

Track::Track(std::string name, std::string fp) : name(name), file_path(fp) {}

const char *Track::get_file_path()
{
  return file_path.c_str();
}