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
      long elapsed = millis() - last_read;
      if (elapsed > CARDREADER_BROADCAST_INTERVAL_MS)
      {
        broadcast_card_read_event();
        last_read = millis();
      }
    }
  }
  rfid.halt();
}

void CardReader::broadcast_card_read_event()
{
  auto card_serial_number = str(rfid.serNum);
  std::stringstream ss;
  ss << "Card Read: " << card_serial_number;
  monitor.print(ss);
  for (auto l : listeners)
  {
    l->on_card_read(card_serial_number);
  }
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
