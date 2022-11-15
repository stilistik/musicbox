#include "Album.hpp"

Album::Album(std::string name) : name(name) {}

void Album::add_track(std::shared_ptr<Track> t)
{
  tracks.push_back(t);
}

std::string Album::get_name()
{
  return name;
}