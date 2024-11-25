#include "./func.hpp"

bool is_hex(std::string input) {
  for (unsigned int i = 0; i < input.length(); i++)
  {
    int uppercase_char = std::toupper(input[i]);
    if (uppercase_char >= 48 && uppercase_char <= 57)
    {
      continue;
    }
    if (uppercase_char < 'A' || uppercase_char > 'F') {
      return false;
    }
  }
  return true;
}