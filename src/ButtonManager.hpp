#ifndef BUTTONMANAGER_HPP
#define BUTTONMANAGER_HPP

#include <vector>
#include <memory>
#include "Button.hpp"

class ButtonManagerListener
{
public:
  virtual void on_button_click(Button *btn) = 0;
  virtual void on_play_album_pressed() = 0;
  virtual void on_play_album_released() = 0;
};

class ButtonManager : public ButtonListener
{
private:
  std::vector<Button *> buttons;
  std::vector<ButtonManagerListener *> listeners;

  void broadcast_click_event(Button *btn);
  void broadcast_play_album_pressed_event();
  void broadcast_play_album_released_event();

  bool play_album_pressed = false;

public:
  ButtonManager();
  void update();
  void register_listener(ButtonManagerListener *l);
  void on_button_down(Button *btn) override;
  void on_button_up(Button *btn) override;
  void on_button_click(Button *btn) override;
  void on_button_long_click(Button *btn) override;
};

#endif /* BUTTONMANAGER_HPP */
