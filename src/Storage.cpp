#include "Storage.hpp"
#include "Monitor.hpp"
#include "Utils.hpp"

Storage::Storage()
{
}

void Storage::setup()
{
  monitor.print("Setting up storage...");
  MTP.begin();

  // Add SD Card
  if (SD.begin(SD_SLOT))
  {
    MTP.addFilesystem(SD, "SD Card");
    monitor.print("Added SD card using built in SDIO, or given SPI CS");
  }
  else
  {
    monitor.print("No SD Card");
  }
  monitor.print("Storage setup complete.");
  setup_successful = true;

  // read the wav files form the SD card
  read_files();
}

void Storage::read_files()
{
  if (!setup_successful)
  {
    return;
  }

  File root = SD.open("/");
  while (true)
  {

    File entry = root.openNextFile();

    if (!entry)
    {
      // no more files
      break;
    }

    if (entry.isDirectory())
    {
      // disregard directories
      continue;
    }

    std::string fn = entry.name();

    if (!str_has_extension(fn, "wav"))
    {
      // disregard non-wav files
      continue;
    }

    if (str_starts_with(fn, "."))
    {
      // disregard hidden files
      continue;
    }

    if (!str_contains_times(fn, DELIMITER, 2))
    {
      // discard files with invalid names
      continue;
    }

    size_t pos = 0;
    std::vector<std::string> track_data;
    auto file_path = fn;
    while ((pos = fn.find(DELIMITER)) != std::string::npos)
    {
      track_data.push_back(fn.substr(0, pos));
      fn.erase(0, pos + std::string(DELIMITER).length());
    }

    auto album = get_album_with_name(track_data[1]);
    std::shared_ptr<Track> track(new Track(fn, file_path, track_data[0]));
    tracks.push_back(track);
    album->add_track(track);

    entry.close();
  }

  std::stringstream ss;
  ss << "Albums: " << albums.size() << " Tracks: " << tracks.size();
  monitor.print(ss);
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
  if (setup_successful)
  {
    MTP.loop();
  }
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