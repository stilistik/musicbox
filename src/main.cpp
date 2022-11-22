#include "Storage.hpp"
#include "Player.hpp"
#include "CardReader.hpp"
#include "ButtonManager.hpp"

Storage storage = Storage();
CardReader reader = CardReader();
ButtonManager btn_mgr = ButtonManager();
Player player = Player(storage, reader);

void setup()
{
  storage.setup();
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
}