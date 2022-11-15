#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>

bool str_has_extension(std::string str, std::string token);
bool str_starts_with(std::string str, std::string token);
int str_count_occurrences(std::string str, std::string token);
bool str_contains(std::string str, std::string token);
bool str_contains_once(std::string str, std::string token);

#endif /* UTILS_HPP_ */
