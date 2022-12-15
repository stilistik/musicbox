#include "Storage.hpp"
#include "Monitor.hpp"
#include "Utils.hpp"
#include <vector>
#include <sstream>
#include <string>

Storage::Storage()
{
}

void Storage::setup()
{
  monitor.print("Setting up storage...");
  // MTP.begin();

  // Add SD Card
  if (SD.begin(SD_SLOT))
  {
    monitor.print("Added SD card using built in SDIO, or given SPI CS");
  }
  else
  {
    monitor.print("No SD Card");
  }
  monitor.print("Storage setup complete.");
  setup_successful = true;

  // read the wav files form the SD card
  // read_files();
  read_index();
}

void Storage::read_index()
{
  if (!setup_successful)
  {
    return;
  }
  if (!SD.exists("index.csv"))
  {
    monitor.print("No index.csv file found.");
    return;
  }
  File file = SD.open("index.csv");

  // Read the file line by line
  while (file.available())
  {
    auto line = std::string(file.readStringUntil('\n').c_str());

    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ';'))
    {
      tokens.push_back(token);
    }

    auto album_name = tokens[0];
    auto track_name = tokens[1];
    auto file_path = tokens[2];
    auto rfid_code = tokens[3];

    auto album = get_album_with_name(album_name);
    std::shared_ptr<Track> track(new Track(track_name, file_path, rfid_code, album));
    tracks.push_back(track);
    album->add_track(track);
  }

  file.close();
}

std::shared_ptr<Album> Storage::get_album_with_name(std::string name)
{
  for (auto album : albums)
  {
    if (album->get_name() == name)
    {
      return album;
    }
  }
  std::shared_ptr<Album> album(new Album(name));
  albums.push_back(album);
  return album;
}

void Storage::update()
{
}

std::shared_ptr<Album> Storage::get_album(int idx)
{
  int index = constrain(idx, 0, albums.size() - 1);
  return albums[index];
}

std::shared_ptr<Track> Storage::get_track_by_rfid(std::string rfid)
{
  for (auto t : tracks)
  {
    if (t->get_rfid() == rfid)
    {
      return t;
    }
  }
  return nullptr;
}

void Storage::write_track_rfid(std::string rfid, std::string fp)
{
  size_t pos = 0;
  std::vector<std::string> track_data;
  auto old_file_path = fp;
  while ((pos = fp.find(DELIMITER)) != std::string::npos)
  {
    track_data.push_back(fp.substr(0, pos));
    fp.erase(0, pos + std::string(DELIMITER).length());
  }

  std::stringstream ss;
  ss << rfid << DELIMITER << track_data[1] << DELIMITER << fp;
  auto new_file_path = ss.str();

  if (SD.exists(old_file_path.c_str()))
  {
    SD.rename(old_file_path.c_str(), new_file_path.c_str());
  }

  auto track = get_track_by_rfid(track_data[0]);
  track->set_rfid(rfid);
}

int Storage::get_album_index(std::shared_ptr<Album> album)
{
  for (int i = 0; i < albums.size(); ++i)
  {
    if (albums[i] == album)
    {
      return i;
    }
  }
  return -1;
}