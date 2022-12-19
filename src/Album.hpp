#ifndef ALBUM_HPP_
#define ALBUM_HPP_

#include <vector>
#include <memory>
#include <Track.hpp>

class Album
{
private:
  int current_track_index = 0;
  std::vector<std::shared_ptr<Track>> tracks;
  std::string name;

public:
  Album(std::string name);
  void add_track(std::shared_ptr<Track> t);
  std::string get_name();
  std::shared_ptr<Track> get_track(int i);
  int size();
  int get_track_index(std::shared_ptr<Track> t);
  std::shared_ptr<Track> get_next_track();
  std::shared_ptr<Track> get_prev_track();
  std::shared_ptr<Track> get_current_track();
};

#endif /* ALBUM_HPP_ */