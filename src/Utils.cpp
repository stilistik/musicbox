#include "Utils.hpp"

bool str_has_extension(std::string str, std::string token)
{
  return str.substr(str.find_last_of(".") + 1) == token;
}

bool str_starts_with(std::string str, std::string token)
{
  return str.rfind(token, 0) == 0;
}

int str_count_occurrences(std::string str, std::string token)
{
  int occurrences = 0;
  size_t pos = 0;
  while ((pos = str.find(token, pos)) != std::string::npos)
  {
    ++occurrences;
    pos += token.length();
  }
  return occurrences;
}

bool str_contains(std::string str, std::string token)
{
  return str_count_occurrences(str, token) > 0;
}

bool str_contains_once(std::string str, std::string token)
{
  return str_count_occurrences(str, token) == 1;
}