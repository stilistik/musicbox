#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include "Arduino.h"
#include <string>
#include <vector>
#include <map>
#include <sstream>

#define LED_PIN 1

class Monitor
{
private:
  unsigned int lastUpdated = 0;
  unsigned int interval = 1000;
  const unsigned int serialConnectTimeout = 3000;
  std::stringstream buffer;

  bool should_print();

public:
  Monitor(unsigned int interval);
  void print(int number);
  void print(float number);
  void print(const char *str);
  void print(std::string str);
  void print(std::vector<int> &vec);
  void print(std::vector<bool> &vec);
  void print(std::map<int, int> &map);
  void print(std::stringstream &ss);
};

extern Monitor monitor;

#endif /* MONITOR_HPP_ */
