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

    if (!str_contains_once(fn, DELIMITER))
    {
      // discard files with invalid names
      continue;
    }

    size_t pos = fn.find(DELIMITER);
    std::string album_name = fn.substr(0, pos);
    std::string track_name = fn.substr(pos + std::string(DELIMITER).length(), fn.length());

    auto album = get_album_with_name(album_name);

    std::shared_ptr<Track> track(new Track(track_name));
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