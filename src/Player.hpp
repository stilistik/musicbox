#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "Storage.hpp"

class Player
{
private:
  AudioPlaySdWav playSdWav1;
  AudioOutputI2S audioOutput;
  AudioConnection patchCord1;
  AudioConnection patchCord2;
  AudioControlSGTL5000 sgtl5000_1;

public:
  Player();

  void setup();
  void update();

  void play_track(std::shared_ptr<Track> track);
  void stop();
};

#endif /* PLAYER_HPP_ */