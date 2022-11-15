#include "Storage.hpp"
#include <memory>

Storage storage;

void setup()
{
  storage.setup();
}

void loop()
{
  storage.update();
}