#include "Monitor.hpp"
#include "Arduino.h"

Monitor monitor = Monitor(0);

Monitor::Monitor(unsigned int interval)
{
  this->interval = interval;

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  unsigned int start = millis();
  unsigned int now = millis();

  // try for 5 seconds to connect to the serial port
  while (!Serial && (now - start < serialConnectTimeout))
  {
    now = millis();
    unsigned int delta = now - start;

    // blink the led during serial monitor connection
    if (delta % 1000 > 500)
    {
      digitalWrite(LED_PIN, HIGH);
    }
    else
    {
      digitalWrite(LED_PIN, LOW);
    }
  }
  Serial.println("Serial connected.");
  digitalWrite(LED_PIN, LOW);
}

bool Monitor::should_print()
{
  unsigned int now = millis();
  if (now - lastUpdated >= interval)
  {
    lastUpdated = now;
    return true;
  }
  else
    return false;
}

void Monitor::print(int number)
{
  if (should_print())
  {
    Serial.println(number);
  }
}

void Monitor::print(int *arr)
{
  if (should_print())
  {
    for (unsigned int i = 0; i <= sizeof(arr); i++)
    {
      Serial.print(arr[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void Monitor::print(unsigned char *arr)
{
  if (should_print())
  {
    for (unsigned int i = 0; i <= sizeof(arr); i++)
    {
      Serial.print(arr[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void Monitor::print(float number)
{
  if (should_print())
  {
    Serial.println(number);
  }
}

void Monitor::print(const char *str)
{
  if (should_print())
  {
    Serial.println(str);
  }
}

void Monitor::print(std::string str)
{
  if (should_print())
  {
    Serial.println(str.c_str());
  }
}

void Monitor::print(std::vector<int> &vec)
{
  if (vec.size() == 0)
    return;
  if (should_print())
  {
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
      Serial.print(vec[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
}

void Monitor::print(std::vector<bool> &vec)
{
  if (vec.size() == 0)
    return;

  if (should_print())
  {
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
      Serial.print(vec[i]);
      Serial.print(" ");
    }
    Serial.println("");
  }
}

void Monitor::print(std::vector<std::string> &vec)
{
  if (vec.size() == 0)
    return;

  if (should_print())
  {
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
      Serial.print(vec[i].c_str());
      Serial.print(" ");
    }
    Serial.println("");
  }
}

void Monitor::print(std::map<int, int> &map)
{
  if (map.size() == 0)
    return;

  if (should_print())
  {

    std::map<int, int>::iterator it;
    for (it = map.begin(); it != map.end(); ++it)
    {
      Serial.print(it->first);
      Serial.print(":");
      Serial.print(it->second);
      Serial.print(" ");
    }
    Serial.println("");
  }
}

void Monitor::print(std::stringstream &ss)
{
  print(ss.str());
}
