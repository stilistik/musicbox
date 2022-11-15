#ifndef TRACK_HPP_
#define TRACK_HPP_

#include <string>

class Track
{
private:
  std::string file_path;

public:
  Track(std::string fp);
  const char *get_file_path();
};

#endif /* TRACK_HPP_ */