#include "Storage.hpp"
#include "Player.hpp"
#include "CardReader.hpp"
#include "ButtonManager.hpp"
#include "LEDController.hpp"

Storage storage = Storage();
CardReader reader = CardReader();
LEDController led_ctrl = LEDController();
ButtonManager btn_mgr = ButtonManager(led_ctrl);
Player player = Player(storage, reader, led_ctrl);

void setup()
{
  storage.setup();
  led_ctrl.setup();
  player.setup();
  reader.setup();
  btn_mgr.setup();
  btn_mgr.register_listener(&player);
}

void loop()
{
  storage.update();
  player.update();
  reader.update();
  btn_mgr.update();
  led_ctrl.update();
}