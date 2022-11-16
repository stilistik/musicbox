#ifndef CARDREADER_HPP
#define CARDREADER_HPP

#include <SPI.h>
#include <RFID.h>
#include <string>
#include <vector>

#define RST_PIN 33
#define NSS_PIN 10

class CardReaderListener
{
public:
  virtual void on_card_read(std::string rfid) = 0;
};

class CardReader
{

private:
  RFID rfid;
  std::vector<CardReaderListener *> listeners;

  std::string str(unsigned char *num);

public:
  CardReader();
  void update();
  void setup();
  void register_listener(CardReaderListener *listener);
};

#endif /* CARDREADER_HPP */