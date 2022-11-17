#include "Track.hpp"
#include "Storage.hpp"
#include "Monitor.hpp"

Track::Track(std::string name, std::string rfid, std::shared_ptr<Album> album)
    : name(name), rfid(rfid), album(album) {}

std::string Track::get_file_path()
{
  std::stringstream ss;
  ss << rfid << DELIMITER << album->get_name() << DELIMITER << name;
  return ss.str();
}

std::string Track::get_rfid()
{
  return rfid;
}

void Track::set_rfid(std::string id)
{
  rfid = id;
}

std::shared_ptr<Album> Track::get_album()
{
  return album;
}
