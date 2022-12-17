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

bool str_contains_times(std::string str, std::string token, int times)
{
  return str_count_occurrences(str, token) == times;
}

int keep_in_bounds(int value, int min, int max)
{
  if (value < min)
  {
    return max;
  }
  else if (value >= max)
  {
    return min;
  }
  else
  {
    return value;
  }
}

std::string replace(const std::string &input, const std::string &substring, const std::string &replacement)
{
  std::string result;
  std::string::size_type start_pos = 0;
  std::string::size_type pos;

  while ((pos = input.find(substring, start_pos)) != std::string::npos)
  {
    result.append(input, start_pos, pos - start_pos);
    result.append(replacement);
    start_pos = pos + substring.length();
  }

  result.append(input, start_pos, input.length() - start_pos);

  return result;
}