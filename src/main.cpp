#include "Storage.hpp"
#include "Player.hpp"

Storage storage;
Player player = Player(storage);

void setup()
{
  storage.setup();
  player.setup();
}

void loop()
{
  storage.update();
  player.update();
}