#ifndef DES_KEY_HPP
#define DES_KEY_HPP

#include <iostream>
#include <bitset>
#include <memory>
#include <vector>

using namespace std;

struct tranformReturn {
  bitset<48> key;
  bitset<28> left_key;
  bitset<28> right_key;
};

class DESKey {
private:
  vector<bitset<48>> keys;
  bitset<64> initial_key;

  bitset<56> contraction_permutation_1(bitset<64> key);
  bitset<48> contraction_permutation_2(bitset<56> key);
  bitset<28> left_shift(bitset<28> bits, unsigned int shifts);

public:
  unsigned int nr_of_keys = 16;

  DESKey(string key = "0") {
    this->initial_key = (bitset<64>)key;
  }

  vector<bitset<48>> get_keys();
};

#endif