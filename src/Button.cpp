#include "Button.hpp"
#include "Arduino.h"
#include "Monitor.hpp"

Button::Button(unsigned int pin, int type) : type(type), bounce(Bounce(pin, 10)) {}

void Button::update()
{
  bounce.update();
  if (bounce.fallingEdge())
  {
    down_time = millis();
    broadcast_down_event();
  }
  if (bounce.risingEdge())
  {
    if (is_pressed())
    {
      long elapsed = millis() - down_time;
      if (elapsed < CLICK_INTERVAL_MS)
      {
        broadcast_click_event();
      }
      else if (elapsed > LONG_CLICK_INTERVAL_MS)
      {
        broadcast_long_click_event();
      }
    }
    down_time = 0;
    broadcast_up_event();
  }
}

void Button::broadcast_click_event()
{
  for (auto l : listeners)
  {
    l->on_button_click(this);
  }
}

void Button::broadcast_long_click_event()
{
  for (auto l : listeners)
  {
    l->on_button_long_click(this);
  }
}

void Button::broadcast_down_event()
{

  for (auto l : listeners)
  {
    l->on_button_down(this);
  }
}
void Button::broadcast_up_event()
{
  for (auto l : listeners)
  {
    l->on_button_up(this);
  }
}

void Button::register_listener(ButtonListener *l)
{
  listeners.push_back(l);
}

int Button::get_type()
{
  return type;
}

bool Button::is_pressed()
{
  return down_time > 0;
}