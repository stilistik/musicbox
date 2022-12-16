#ifndef TRACK_HPP_
#define TRACK_HPP_

#include <string>
#include <memory>
#include <sstream>

class Album;

class Track
{
private:
  std::string name;
  std::string file_path;
  std::string rfid;
  std::shared_ptr<Album> album;

public:
  Track(std::string name, std::string file_path, std::string rfid_code, std::shared_ptr<Album> album);
  std::string get_file_path();
  std::string get_rfid();
  void set_rfid(std::string rfid);
  std::shared_ptr<Album> get_album();
  std::string get_index_data();
};

#endif /* TRACK_HPP_ */