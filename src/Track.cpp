#include "Track.hpp"

Track::Track(std::string fp) : file_path(fp) {}

const char *Track::get_file_path()
{
  return file_path.c_str();
}