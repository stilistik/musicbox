#include "Player.hpp"
#include "Monitor.hpp"

Player::Player()
    : playSdWav1(AudioPlaySdWav()),
      audioOutput(AudioOutputI2S()),
      patchCord1(AudioConnection(playSdWav1, 0, audioOutput, 0)),
      patchCord2(AudioConnection(playSdWav1, 1, audioOutput, 1)),
      sgtl5000_1(AudioControlSGTL5000())
{
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
}

void Player::update()
{
  if (playSdWav1.isPlaying() == false)
  {
    monitor.print("Start playing");
    playSdWav1.play("album1__song1.WAV");
    delay(10); // wait for library to parse WAV info
  }

  // print the play time offset
  monitor.print("Playing, now at ");
  monitor.print(playSdWav1.positionMillis());
  monitor.print(" ms");
}

void Player::play_track(std::shared_ptr<Track> track)
{
  playSdWav1.play(track->get_file_path());
}

void Player::stop()
{
  playSdWav1.stop();
}