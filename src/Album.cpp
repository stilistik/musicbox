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

int Album::get_track_index(std::shared_ptr<Track> t)
{
  for (int i = 0; i < tracks.size(); ++i)
  {
    if (tracks[i] == t)
    {
      return i;
    }
  }
  return -1;
}

std::shared_ptr<Track> Album::get_next_track()
{
  current_track_index = constrain(current_track_index + 1, 0, tracks.size() - 1);
  return tracks.at(current_track_index);
}

std::shared_ptr<Track> Album::get_prev_track()
{
  current_track_index = constrain(current_track_index - 1, 0, tracks.size() - 1);
  return tracks.at(current_track_index);
}

std::shared_ptr<Track> Album::get_current_track()
{
  return tracks.at(current_track_index);
}