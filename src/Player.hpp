#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "Storage.hpp"
#include "CardReader.hpp"
#include "ButtonManager.hpp"

#define PLAY_BUTTON_PIN 29
#define NEXT_BUTTON_PIN 31
#define PREV_BUTTON_PIN 30
#define ALBUM_BUTTON_PIN 32
#define VOLUME_PIN 27
#define HEADPHONE_PIN 26

#define PLAYER_MODE_RFID_READ 0
#define PLAYER_MODE_RFID_WRITE 1

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class Player : public CardReaderListener, public ButtonManagerListener
{
private:
  Storage &storage;
  CardReader &reader;

  AudioPlaySdWav playSdWav1;
  AudioInputI2S i2s2;
  AudioMixer4 mixer1;
  AudioMixer4 mixer2;
  AudioOutputI2S i2s1;
  AudioConnection patchCord1;
  AudioConnection patchCord2;
  AudioConnection patchCord3;
  AudioConnection patchCord4;
  AudioConnection patchCord5;
  AudioConnection patchCord6;
  AudioControlSGTL5000 sgtl5000_1;

  int current_track = 0;
  int current_album = 0;
  int player_mode = PLAYER_MODE_RFID_READ;

  void update_buttons();
  void on_play();
  void on_next();
  void on_prev();
  void on_album();
  void update_volume();
  void play_track(std::shared_ptr<Track> t);

public:
  Player(Storage &storage, CardReader &reader);
  void setup();
  void update();
  void on_card_read(std::string rfid) override;
  void on_button_click(Button *btn) override;
  void on_play_album_pressed() override;
  void on_play_album_released() override;
};

#endif /* PLAYER_HPP_ */