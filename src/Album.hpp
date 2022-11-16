#ifndef ALBUM_HPP_
#define ALBUM_HPP_

#include <vector>
#include <memory>
#include <Track.hpp>

class Album
{
private:
  std::vector<std::shared_ptr<Track>> tracks;
  std::string name;

public:
  Album(std::string name);
  void add_track(std::shared_ptr<Track> t);
  std::string get_name();
  std::shared_ptr<Track> get_track(int i);
  int size();
};

#endif /* ALBUM_HPP_ */