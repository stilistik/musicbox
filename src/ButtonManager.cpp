#include "ButtonManager.hpp"
#include "Monitor.hpp"
#include <algorithm>

ButtonManager::ButtonManager(LEDController &led_ctrl) : led_ctrl(led_ctrl),
                                                        buttons({
                                                            new Button(PLAY_BUTTON_PIN, PLAY_BUTTON_TYPE),
                                                            new Button(NEXT_BUTTON_PIN, NEXT_BUTTON_TYPE),
                                                            new Button(PREV_BUTTON_PIN, PREV_BUTTON_TYPE),
                                                            new Button(ALBUM_BUTTON_PIN, ALBUM_BUTTON_TYPE),
                                                        })
{
}

void ButtonManager::setup()
{
  for (auto btn : buttons)
  {
    btn->register_listener(this);
  }
}

void ButtonManager::register_listener(ButtonManagerListener *l)
{
  listeners.push_back(l);
}

void ButtonManager::update()
{
  for (auto btn : buttons)
  {
    btn->update();
  }
}

void ButtonManager::broadcast_click_event(Button *btn)
{
  if (play_album_pressed)
  {
    return;
  }
  for (auto l : listeners)
  {
    l->on_button_click(btn);
  }
}

void ButtonManager::on_button_down(Button *btn)
{
  if (buttons[PLAY_BUTTON_TYPE]->is_pressed() && buttons[ALBUM_BUTTON_TYPE]->is_pressed())
  {
    play_album_pressed = true;
    broadcast_play_album_pressed_event();
  }
  led_ctrl.flash(btn->get_type());
}

void ButtonManager::on_button_up(Button *btn)
{
  if (play_album_pressed)
  {
    if (!buttons[PLAY_BUTTON_TYPE]->is_pressed() || !buttons[ALBUM_BUTTON_TYPE]->is_pressed())
    {
      play_album_pressed = false;
      broadcast_play_album_released_event();
    }
  }
}

void ButtonManager::broadcast_play_album_pressed_event()
{
  monitor.print("play/album pressed");
  for (auto l : listeners)
  {
    l->on_play_album_pressed();
  }
}

void ButtonManager::broadcast_play_album_released_event()
{
  monitor.print("play/album released");
  for (auto l : listeners)
  {
    l->on_play_album_released();
  }
}

void ButtonManager::on_button_click(Button *btn)
{
  broadcast_click_event(btn);
}

void ButtonManager::on_button_long_click(Button *btn)
{
  monitor.print("Long click");
}
