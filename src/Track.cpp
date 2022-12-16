#include "Track.hpp"
#include "Storage.hpp"
#include "Monitor.hpp"

Track::Track(std::string name, std::string fp, std::string rfid, std::shared_ptr<Album> album)
    : name(name), file_path(fp), rfid(rfid), album(album) {}

std::string Track::get_file_path()
{
  return file_path;
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

std::string Track::get_index_data()
{
  std::stringstream ss;
  ss << album->get_name() << ';' << name << ';' << file_path << ';' << rfid << ';';
  return ss.str();
}