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

  File file = SD.open("index.csv");
  if (!file)
  {
    monitor.print("No index.csv file found.");
    return;
  }

  unsigned int lineIndex = 0;
  // Read the file line by line
  while (file.available())
  {
    auto line = std::string(file.readStringUntil('\n').c_str());
    lineIndex++;

    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ';'))
    {
      tokens.push_back(token);
    }

    if (tokens.size() < 4)
    {
      std::stringstream ss;
      ss << "ERROR: Malformed index.csv received. Error on line " << lineIndex;
      monitor.print(ss);
      return;
    }

    auto album_name = tokens.at(0);
    auto track_name = tokens.at(1);
    auto file_path = tokens.at(2);
    auto rfid_code = tokens.at(3);

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

void Storage::write_track_rfid(std::string rfid, std::shared_ptr<Track> track)
{
  File file = SD.open("index.csv", FILE_WRITE);
  if (!file)
  {
    monitor.print("No index.csv file found.");
    return;
  }

  auto old_line = track->get_index_data();
  track->set_rfid(rfid);
  auto new_line = track->get_index_data();

  // Read the file line by line
  while (file.available())
  {
    auto line = std::string(file.readStringUntil('\n').c_str());
    if (line == old_line)
    {
      file.println(new_line.c_str());
    }
    else
    {
      file.println(line.c_str());
    }
  }

  file.close();
}

int Storage::get_album_index(std::shared_ptr<Album> album)
{
  for (size_t i = 0; i < albums.size(); ++i)
  {
    if (albums[i] == album)
    {
      return i;
    }
  }
  return -1;
}

int Storage::get_album_count()
{
  return albums.size();
}