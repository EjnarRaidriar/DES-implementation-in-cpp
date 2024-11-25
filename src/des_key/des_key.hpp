#ifndef DES_KEY_HPP
#define DES_KEY_HPP

#include <iostream>
#include <bitset>
#include <memory>
#include <vector>
#include <fstream>

using namespace std;

class DESKey {
private:
  vector<bitset<48>> keys;
  bitset<64> initial_key;

  string file_name;
  ofstream output_file;

  bitset<56> contraction_permutation_1(bitset<64> key);
  bitset<48> contraction_permutation_2(bitset<56> key);
  bitset<28> left_shift(bitset<28> bits, unsigned int shifts);

public:
  unsigned int nr_of_keys = 16;

  DESKey(string key = "0")
    : file_name("output.txt"), output_file(file_name)
  {
    this->initial_key = (bitset<64>)key;
    if (!output_file) {
      cout << "File not found!" << endl;
    }
  }

  vector<bitset<48>> get_keys();
  string get_output_file_name();
};

#endif