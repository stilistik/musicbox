#include "Album.hpp"
#include "Arduino.h"

Album::Album(std::string name) : name(name) {}

void Album::add_track(std::shared_ptr<Track> t)
{
  tracks.push_back(t);
}

std::string Album::get_name()
{
  return name;
}

std::shared_ptr<Track> Album::get_track(int i)
{
  int index = constrain(i, 0, tracks.size() - 1);
  return tracks[index];
}

int Album::size()
{
  return tracks.size();
}
