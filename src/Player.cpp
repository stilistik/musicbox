#include "Player.hpp"
#include "Monitor.hpp"
#include "Utils.hpp"

Player::Player(Storage &storage, CardReader &reader, LEDController &led_ctrl)
    : storage(storage),
      reader(reader),
      led_ctrl(led_ctrl),
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
  // maxing this out will add noise to headphones
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
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
  if (playSdWav1.isPlaying() && playSdWav1.lengthMillis() - playSdWav1.positionMillis() < 500)
  {
    on_next();
  }
  update_volume();
}

void Player::on_play()
{
  if (playSdWav1.isStopped())
  {
    monitor.print("PLAY");
    current_album = storage.get_next_album(current_album);
    current_track = current_album->get_current_track();
    play_track(current_track);
  }
  else
  {
    playSdWav1.togglePlayPause();
  }
}

void Player::on_next()
{
  monitor.print("NEXT");
  if (!current_album || !current_album->has_next())
  {
    current_album = storage.get_next_album(current_album);
  }
  current_track = current_album->get_next_track();
  play_track(current_track);
}

void Player::on_prev()
{
  monitor.print("PREV");
  if (playSdWav1.positionMillis() > 3000 && current_track)
  {
    play_track(current_track);
  }
  else
  {
    if (!current_album)
    {
      current_album = storage.get_next_album(current_album);
    }
    current_track = current_album->get_prev_track();
    play_track(current_track);
  }
}

void Player::on_album()
{
  monitor.print("ALBUM");
  current_album = storage.get_next_album(current_album);
  current_track = current_album->get_current_track();
  play_track(current_track);
}

void Player::play_track(std::shared_ptr<Track> track)
{
  auto fp = track->get_file_path();
  std::stringstream ss;
  ss << "Playing file " << fp;
  monitor.print(ss);

  playSdWav1.stop();
  delay(200);

  if (!SD.exists(fp.c_str()))
  {
    std::stringstream ss;
    ss << "File " << fp << " does not exist.";
    monitor.print(ss);
    return;
  }

  playSdWav1.play(fp.c_str());
}

void Player::update_volume()
{
  int hpv = analogRead(HEADPHONE_PIN);

  if (hpv > 200)
  {
    sgtl5000_1.unmuteLineout();
  }
  else
  {
    sgtl5000_1.muteLineout();
  }

  int value = 1023 - analogRead(VOLUME_PIN);
  if (abs(prev_value - value) > 5)
  {
    float volume = (float)value / 1023;
    mixer1.gain(0, volume);
    mixer2.gain(0, volume);
    prev_value = value;
  }
}

void Player::on_card_read(std::string rfid)
{
  led_ctrl.run_sequence();
  if (player_mode == PLAYER_MODE_RFID_READ)
  {
    auto track = storage.get_track_by_rfid(rfid);

    if (track)
    {
      if (track.get() == current_track.get())
      {
        // read rfid represents track that is currently playing
        if (playSdWav1.isPaused())
        {
          playSdWav1.togglePlayPause();
        }
        return;
      }
      else
      {
        monitor.print(std::string(track->get_file_path()));
        current_album = track->get_album();
        current_album->set_current_track(track);
        current_track = track;
        play_track(track);
      }
    }
  }
  else if (player_mode == PLAYER_MODE_RFID_WRITE)
  {
    playSdWav1.stop();
    delay(200);
    storage.write_track_rfid(rfid, current_track);
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
}

void Player::on_play_album_released()
{
}

void Player::on_prev_next_pressed()
{
  player_mode = PLAYER_MODE_RFID_WRITE;
}

void Player::on_prev_next_released()
{
  player_mode = PLAYER_MODE_RFID_READ;
}