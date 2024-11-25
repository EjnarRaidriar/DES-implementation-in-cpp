#include "./des/des.hpp"
#include "./conversion/conversion.hpp"
#include "./input/input.hpp"

int main() {
  while (true) {
    int choice_input = input::option();
    if (choice_input == 0) {
      return 0;
    }
    cout << "Enter message" << endl;
    string message = input::sixteen_hex();
    cout << "Enter key" << endl;
    string key = input::sixteen_hex();
    DES cipher = DES(hex_to_bin(key));
    if (choice_input == 1) {
      string encrypted_message = cipher.encrypt(hex_to_bin(message)).to_string();
      cout << "Encrypted Message:" << endl;
      cout << bin_to_hex(encrypted_message) << endl;
    }
    if (choice_input == 2) {
      string decrypted_message = cipher.decrypt(hex_to_bin(message)).to_string();
      cout << "Decrypted Message:" << endl;
      cout << bin_to_hex(decrypted_message) << endl;
    }
  }
  return 0;
}