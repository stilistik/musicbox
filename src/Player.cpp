#include "Player.hpp"
#include "Monitor.hpp"

Player::Player(Storage &storage, CardReader &reader)
    : storage(storage),
      reader(reader),
      playSdWav1(AudioPlaySdWav()),
      i2s2(AudioInputI2S()),
      mixer1(AudioMixer4()),
      mixer2(AudioMixer4()),
      i2s1(AudioOutputI2S()),
      patchCord1(AudioConnection(playSdWav1, 0, mixer1, 0)),
      patchCord2(AudioConnection(playSdWav1, 1, mixer2, 0)),
      patchCord3(AudioConnection(i2s2, 0, mixer1, 1)),
      patchCord4(AudioConnection(i2s2, 0, mixer2, 1)),
      patchCord5(AudioConnection(mixer1, 0, i2s1, 0)),
      patchCord6(AudioConnection(mixer2, 0, i2s1, 1)),
      sgtl5000_1(AudioControlSGTL5000())
{
  reader.register_listener(this);
}

void Player::setup()
{
  AudioMemory(8);
  sgtl5000_1.volume(0.5); // increasing this will add background noise to headphones
  sgtl5000_1.enable();
  mixer1.gain(0, 0.4);
  mixer2.gain(0, 0.4);
  mixer1.gain(1, 0.4);
  mixer2.gain(1, 0.4);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(32);
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
  update_volume();
}

void Player::on_play()
{
  if (playSdWav1.isStopped())
  {
    monitor.print("PLAY");
    auto album = storage.get_album(current_album);
    auto track = album->get_track(current_track);
    playSdWav1.play(track->get_file_path().c_str());
  }
  else
  {
    playSdWav1.togglePlayPause();
  }
}

void Player::on_next()
{
  monitor.print("NEXT");
  auto album = storage.get_album(current_album);
  current_track = constrain(++current_track, 0, album->size());
  auto track = album->get_track(current_track);
  playSdWav1.play(track->get_file_path().c_str());
}

void Player::on_prev()
{
  monitor.print("PREV");
  auto album = storage.get_album(current_album);
  current_track = constrain(--current_track, 0, album->size());
  auto track = album->get_track(current_track);
  playSdWav1.play(track->get_file_path().c_str());
}

void Player::on_album()
{
  monitor.print("ALBUM");
}

void Player::update_volume()
{
  int value = analogRead(VOLUME_PIN);
  float volume = (float)value / 1023;
  mixer1.gain(0, volume);
  mixer2.gain(0, volume);
}

void Player::on_card_read(std::string rfid)
{
  if (player_mode == PLAYER_MODE_RFID_READ)
  {
    auto track = storage.get_track_by_rfid(rfid);
    if (track)
    {
      monitor.print(std::string(track->get_file_path()));
      current_album = storage.get_album_index(track->get_album());
      current_track = track->get_album()->get_track_index(track);
      playSdWav1.play(track->get_file_path().c_str());
    }
  }
  else if (player_mode == PLAYER_MODE_RFID_WRITE)
  {
    playSdWav1.stop();
    delay(10); // give time to close files
    auto album = storage.get_album(current_album);
    auto track = album->get_track(current_track);
    storage.write_track_rfid(rfid, track->get_file_path());
  }
}

void Player::on_button_click(Button *btn)
{
  switch (btn->get_type())
  {
  case PLAY_BUTTON_TYPE:
    on_play();
    break;
  case NEXT_BUTTON_TYPE:
    on_next();
    break;
  case PREV_BUTTON_TYPE:
    on_prev();
    break;
  case ALBUM_BUTTON_TYPE:
    on_album();
    break;
  default:
    break;
  }
}

void Player::on_play_album_pressed()
{
  player_mode = PLAYER_MODE_RFID_WRITE;
}

void Player::on_play_album_released()
{
  player_mode = PLAYER_MODE_RFID_READ;
}