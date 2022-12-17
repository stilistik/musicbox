#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Bounce.h>
#include <vector>
#include <string>

#define CLICK_INTERVAL_MS 3000
#define LONG_CLICK_INTERVAL_MS 3000

#define PLAY_BUTTON_PIN 29
#define NEXT_BUTTON_PIN 31
#define PREV_BUTTON_PIN 30
#define ALBUM_BUTTON_PIN 32

#define PLAY_BUTTON_TYPE 0
#define PREV_BUTTON_TYPE 1
#define NEXT_BUTTON_TYPE 2
#define ALBUM_BUTTON_TYPE 3

class Button;

class ButtonListener
{
public:
  virtual void on_button_click(Button *btn) = 0;
  virtual void on_button_long_click(Button *btn) = 0;
  virtual void on_button_down(Button *btn) = 0;
  virtual void on_button_up(Button *btn) = 0;
};

class Button
{
private:
  int type;
  Bounce bounce;
  long down_time = 0;
  std::vector<ButtonListener *> listeners;
  void broadcast_click_event();
  void broadcast_long_click_event();
  void broadcast_down_event();
  void broadcast_up_event();

public:
  Button(unsigned int pin, int type);
  void update();
  void register_listener(ButtonListener *listener);
  int get_type();
  bool is_pressed();
};

#endif /* BUTTON_HPP */