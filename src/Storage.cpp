#include "Storage.hpp"
#include "Monitor.hpp"
#include "Utils.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

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
    restore_index_from_backup();
    return;
  }

  unsigned int lineIndex = 0;
  // Read the file line by line
  while (file.available())
  {
    auto line = std::string(file.readStringUntil('\n').c_str());
    index_content.push_back(line);
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

      file.close();
      restore_index_from_backup();
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

  monitor.print(index_content);

  file.close();
}

void Storage::restore_index_from_backup()
{
  monitor.print("Restoring index.csv from backup.");

  // read from the original file
  File backup = SD.open("backup.csv");
  if (!backup)
  {
    monitor.print("Error opening backup.csv file");
    return;
  }

  SD.remove("index.csv");
  File index = SD.open("index.csv", FILE_WRITE);
  if (!index)
  {
    monitor.print("Error creating index.csv file");
    return;
  }

  // read the contents of the original file and write them to the copy file
  while (backup.available())
  {
    index.write(backup.read());
  }

  backup.close();
  index.close();
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
  monitor.print("A");

  File file = SD.open("index.csv", FILE_WRITE_BEGIN);
  if (!file)
  {
    monitor.print("Error opening writable index.csv file.");
    return;
  }

  monitor.print("B");

  auto old_track = get_track_by_rfid(rfid);
  if (old_track != nullptr)
  {
    old_track->set_rfid("-1");
  }

  monitor.print("C");

  auto old_rfid = track->get_rfid();
  track->set_rfid(rfid);

  monitor.print("D");

  // Read and process each line of the file
  for (auto &line : index_content)
  {
    // Modify the line if necessary
    if (str_contains(line, track->get_file_path()))
    {
      file.println(track->get_index_data().c_str());
    }
    else if (str_contains(line, rfid))
    {
      file.println(replace(line, rfid, "-1").c_str());
    }
    else
    {
      file.println(line.c_str());
    }
  }
  file.close();
}

std::shared_ptr<Album> Storage::get_next_album(std::shared_ptr<Album> current_album)
{
  auto it = std::find(albums.begin(), albums.end(), current_album);
  if (it != albums.end())
  {
    auto index = keep_in_bounds(std::distance(albums.begin(), it) + 1, 0, albums.size() - 1);
    return albums.at(index);
  }
  else
  {
    return albums.at(0);
  }
}
