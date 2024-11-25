#include "./input.hpp"
#include "./func/func.hpp"

#include <limits>
using namespace input;

int input::option() {
  while (true) {
    std::cout << "Choose an option:" << std::endl;
    std::cout << "Encrypt: 1" << std::endl;
    std::cout << "Decrypt: 2" << std::endl;
    std::cout << "Exit: 0" << std::endl;
    std::cout << "Option -> ";
    int option;
    std::cin >> option;
    switch(option) {
      case 1:
        return option;
      case 2:
        return option;
      case 0:
        return option;
      default:
        std::cout << "Invalid Option!" << std::endl;
    }
  }
}


std::string input::sixteen_hex() {
  while (true) {
    std::string input;
    std::cout << "-> ";
    if (std::cin>>input) {
      std::cin.ignore();
    } else {
      std::cin.ignore(INT_MAX, '\n');
      std::cin.clear();
    }
    if (input.length() != 16)
    {
      std::cout << "The length should be 16!" << std::endl;
      continue;
    }
    if (is_hex(input) == false)
    {
      std::cout << "Input is not HEX value!" << std::endl;
      continue;
    }
    else
      return input;
  }
}