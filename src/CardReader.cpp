#include <SPI.h>
#include "CardReader.hpp"
#include "Monitor.hpp"

CardReader::CardReader() : rfid(RFID(NSS_PIN, RST_PIN)) {}

void CardReader::setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void CardReader::update()
{
  if (rfid.isCard())
  {
    if (rfid.readCardSerial())
    {
      auto s = str(rfid.serNum);
      monitor.print(s);
      for (auto l : listeners)
      {
        l->on_card_read(s);
      }
    }
  }
  rfid.halt();
}

std::string CardReader::str(unsigned char *num)
{
  std::stringstream ss;
  for (unsigned int i = 0; i < sizeof(rfid.serNum); i++)
  {
    ss << (int)(num[i]);
  }
  return ss.str();
}

void CardReader::register_listener(CardReaderListener *listener)
{
  listeners.push_back(listener);
}