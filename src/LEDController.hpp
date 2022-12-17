#ifndef LEDCONTROLLER_HPP
#define LEDCONTROLLER_HPP

#include <vector>

#define PLAY_BUTTON_LED_PIN 36
#define NEXT_BUTTON_LED_PIN 34
#define PREV_BUTTON_LED_PIN 35
#define ALBUM_BUTTON_LED_PIN 33

#define FLASH_MS 400
#define FLASH_LONG_MS 1200
#define SEQUENCE_DELAY 100

class LEDController
{
private:
  bool sequence_running = false;
  unsigned long flash_end_time = -1;
  int flash_pin = -1;
  unsigned long lastLEDUpdateTime = 0;
  int current_index = 0;
  int sequence_increment = 1;
  void update_sequence();
  std::vector<int> ledpins = {
      PLAY_BUTTON_LED_PIN,
      PREV_BUTTON_LED_PIN,
      NEXT_BUTTON_LED_PIN,
      ALBUM_BUTTON_LED_PIN,
  };

public:
  void update();
  void setup();

  void flash(int pin);
  void flash_long(int pin);
  void run_sequence();
};

#endif /* LEDCONTROLLER_HPP */