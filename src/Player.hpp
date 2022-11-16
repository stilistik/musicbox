#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "Storage.hpp"

#define PLAY_BUTTON_PIN 29
#define NEXT_BUTTON_PIN 31
#define PREV_BUTTON_PIN 30
#define ALBUM_BUTTON_PIN 32
#define VOLUME_PIN 27

class Player
{
private:
  Storage &storage;

  AudioPlaySdWav playSdWav1;
  AudioOutputI2S audioOutput;
  AudioConnection patchCord1;
  AudioConnection patchCord2;
  AudioControlSGTL5000 sgtl5000_1;

  Bounce play_button = Bounce(PLAY_BUTTON_PIN, 10);
  Bounce next_button = Bounce(NEXT_BUTTON_PIN, 10);
  Bounce prev_button = Bounce(PREV_BUTTON_PIN, 10);
  Bounce album_button = Bounce(ALBUM_BUTTON_PIN, 10);

  int current_track = 0;
  int current_album = 0;

  void update_buttons();
  void update_play_button();
  void update_next_button();
  void update_prev_button();
  void update_album_button();
  void update_volume();

public:
  Player(Storage &storage);
  void setup();
  void update();
};

#endif /* PLAYER_HPP_ */