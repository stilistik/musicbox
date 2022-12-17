#include "LEDController.hpp"
#include "Arduino.h"
#include "Monitor.hpp"

void LEDController::setup()
{
  pinMode(PLAY_BUTTON_LED_PIN, OUTPUT);
  pinMode(NEXT_BUTTON_LED_PIN, OUTPUT);
  pinMode(PREV_BUTTON_LED_PIN, OUTPUT);
  pinMode(ALBUM_BUTTON_LED_PIN, OUTPUT);
}

void LEDController::update()
{
  if (sequence_running)
  {
    update_sequence();
  }
  if (flash_pin && flash_end_time < millis())
  {
    digitalWrite(flash_pin, LOW);
    flash_pin = -1;
    flash_end_time = -1;
  }
}

void LEDController::update_sequence()
{

  if (millis() - lastLEDUpdateTime >= SEQUENCE_DELAY)
  {
    int led_pin = ledpins.at(current_index);

    digitalWrite(led_pin, HIGH);

    int prev_index = current_index - sequence_increment;
    current_index += sequence_increment;

    if (prev_index >= 0 && prev_index <= 3)
    {
      int prev_led_pin = ledpins.at(prev_index);
      digitalWrite(prev_led_pin, LOW);
    }

    if (current_index > 3)
    {
      sequence_increment = -1;
      current_index = 2;
    }
    if (current_index < 0)
    {
      sequence_increment = 1;
      current_index = 0;
      sequence_running = false;
      delay(SEQUENCE_DELAY);
      digitalWrite(led_pin, LOW);
    }

    lastLEDUpdateTime = millis();
  }
}

void LEDController::flash(int pin_index)
{
  if (sequence_running || flash_pin > -1)
  {
    return;
  }
  monitor.print("TEST");
  flash_end_time = millis() + FLASH_MS;
  flash_pin = ledpins.at(pin_index);
  digitalWrite(flash_pin, HIGH);
}

void LEDController::flash_long(int pin_index)
{
  if (sequence_running || flash_pin > -1)
  {
    return;
  }
  flash_end_time = millis() + FLASH_LONG_MS;
  flash_pin = ledpins.at(pin_index);
  digitalWrite(flash_pin, HIGH);
}

void LEDController::run_sequence()
{
  sequence_running = true;
}
