#include "Storage.hpp"
#include "Player.hpp"
#include "CardReader.hpp"

Storage storage = Storage();
CardReader reader = CardReader();
Player player = Player(storage, reader);

void setup()
{
  storage.setup();
  player.setup();
  reader.setup();
}

void loop()
{
  storage.update();
  player.update();
  reader.update();
}