#include <algorithm>
#include "Album.hpp"
#include "Utils.hpp"
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

int Album::size()
{
  return tracks.size();
}

void Album::set_current_track(std::shared_ptr<Track> t)
{
  auto it = std::find(tracks.begin(), tracks.end(), t);
  if (it != tracks.end())
  {
    current_track_index = keep_in_bounds(std::distance(tracks.begin(), it), 0, tracks.size() - 1);
  }
  else
  {
    current_track_index = 0;
  }
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