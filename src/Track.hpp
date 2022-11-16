#ifndef TRACK_HPP_
#define TRACK_HPP_

#include <string>

class Track
{
private:
  std::string name;
  std::string file_path;
  std::string rfid;

public:
  Track(std::string name, std::string fp, std::string rfid);
  const char *get_file_path();
  std::string get_rfid();
};

#endif /* TRACK_HPP_ */