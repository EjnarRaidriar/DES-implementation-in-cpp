#ifndef DES_HPP
#define DES_HPP

#include <iostream>
#include <bitset>

#include "../des_key/des_key.hpp"

using namespace std;

class DES {
private:
  DESKey key;

  bitset<48> expansion_permutation(bitset<32> bits);
  bitset<6> subbits(unsigned int nr, bitset<48> bits);
  bitset<4> s_box_substitution(unsigned int nr, bitset<6> bits);
  bitset<32> s_box(bitset<48> bits);
  bitset<32> f_function(bitset<32> bits, bitset<48> key);
  bitset<64> encryption_decryption_function(string message, vector < bitset<48>> keys);

public:
  DES(string key) {
    this->key = DESKey(key);
  }

  bitset<64> encrypt(string message);
  bitset<64> decrypt(string message);
};

#endif