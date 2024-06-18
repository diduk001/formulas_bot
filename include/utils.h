//
// Created by f4s4r on 6/18/24.
//

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <string>
#include <regex>

bool isValidEmail(const std::string &email) {
  return std::regex_match(email, regular_expressions::pattern);
}

#include "constants.h"

namespace utils {
bool isValidEmail(const std::string &email) { return true; }
}  // namespace utils

#endif  // INCLUDE_UTILS_H_
