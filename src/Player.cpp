#include "Player.hpp"
#include "Monitor.hpp"

Player::Player(Storage &storage, CardReader &reader)
    : storage(storage),
      reader(reader),
      playSdWav1(AudioPlaySdWav()),
      audioOutput(AudioOutputI2S()),
      patchCord1(AudioConnection(playSdWav1, 0, audioOutput, 0)),
      patchCord2(AudioConnection(playSdWav1, 1, audioOutput, 1)),
      sgtl5000_1(AudioControlSGTL5000())
{
  reader.register_listener(this);
}

void Player::setup()
{
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.45);
  if (!(SD.begin(SD_SLOT)))
  {
    while (1)
    {
      monitor.print("Unable to access the SD card");
      delay(500);
    }
  }

  pinMode(PLAY_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(NEXT_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(PREV_BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(ALBUM_BUTTON_PIN, INPUT_PULLDOWN);
}

void Player::update()
{
  update_buttons();
}

void Player::update_buttons()
{
  update_album_button();
  update_prev_button();
  update_next_button();
  update_play_button();
  update_volume();
}

void Player::update_play_button()
{
  play_button.update();
  if (play_button.risingEdge())
  {
    if (playSdWav1.isStopped())
    {
      monitor.print("PLAY");
      auto album = storage.get_album(current_album);
      auto track = album->get_track(current_track);
      playSdWav1.play(track->get_file_path());
    }
    else
    {
      playSdWav1.togglePlayPause();
    }
  }
}

void Player::update_next_button()
{
  next_button.update();
  if (next_button.risingEdge())
  {
    monitor.print("NEXT");
    auto album = storage.get_album(current_album);
    current_track = constrain(++current_track, 0, album->size());
    auto track = album->get_track(current_track);
    playSdWav1.play(track->get_file_path());
  }
}

void Player::update_prev_button()
{
  prev_button.update();
  if (prev_button.risingEdge())
  {
    monitor.print("PREV");
    auto album = storage.get_album(current_album);
    current_track = constrain(--current_track, 0, album->size());
    auto track = album->get_track(current_track);
    playSdWav1.play(track->get_file_path());
  }
}
void Player::update_album_button()
{
  album_button.update();
  if (album_button.risingEdge())
  {
    monitor.print("ALBUM");
  }
}

void Player::update_volume()
{
  int value = analogRead(VOLUME_PIN);
  float volume = (float)value / 1023;
  sgtl5000_1.volume(volume);
}

void Player::on_card_read(std::string rfid)
{
  auto track = storage.get_track_by_rfid(rfid);
  if (track)
  {
    playSdWav1.play(track->get_file_path());
  }
}