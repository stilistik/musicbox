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
    std::string song_name = fn.substr(pos + std::string(DELIMITER).length(), fn.length());

    auto it = content.find(album_name);
    if (it != content.end())
    {
      it->second.push_back(song_name);
    }
    else
    {
      std::vector<std::string> vec = {song_name};
      content.insert({album_name, vec});
    }
  }
}

void Storage::update()
{
  if (setup_successful)
  {
    MTP.loop();
  }
}