#include "./conversion.hpp"

#include <bitset>

std::string bin_to_hex(std::string bits) {
  std::string hex = "";
  for (unsigned int i = 0; i < bits.length(); i += 4) {
    std::string bin = "";
    for (unsigned int j = i; j < i + 4; j++)
      bin += bits[j];
    if (bin == "0000")
      hex += '0';
    else if (bin == "0001")
      hex += '1';
    else if (bin == "0010")
      hex += '2';
    else if (bin == "0011")
      hex += '3';
    else if (bin == "0100")
      hex += '4';
    else if (bin == "0101")
      hex += '5';
    else if (bin == "0110")
      hex += '6';
    else if (bin == "0111")
      hex += '7';
    else if (bin == "1000")
      hex += '8';
    else if (bin == "1001")
      hex += '9';
    else if (bin == "1010")
      hex += 'A';
    else if (bin == "1011")
      hex += 'B';
    else if (bin == "1100")
      hex += 'C';
    else if (bin == "1101")
      hex += 'D';
    else if (bin == "1110")
      hex += 'E';
    else if (bin == "1111")
      hex += 'F';
  }
  return hex;
}

std::string hex_to_bin(std::string hex) {
  std::string bin = "";
  for (unsigned int i = 0; i < hex.length(); i++) {
    switch (hex[i]) {
      case '0': bin += "0000"; break;
      case '1': bin += "0001"; break;
      case '2': bin += "0010"; break;
      case '3': bin += "0011"; break;
      case '4': bin += "0100"; break;
      case '5': bin += "0101"; break;
      case '6': bin += "0110"; break;
      case '7': bin += "0111"; break;
      case '8': bin += "1000"; break;
      case '9': bin += "1001"; break;
      case 'A':
      case 'a': bin += "1010"; break;
      case 'B':
      case 'b': bin += "1011"; break;
      case 'C':
      case 'c': bin += "1100"; break;
      case 'D':
      case 'd': bin += "1101"; break;
      case 'E':
      case 'e': bin += "1110"; break;
      case 'F':
      case 'f': bin += "1111"; break;
		}
  }
  return bin;
}