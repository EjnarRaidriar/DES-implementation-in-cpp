#include "../cipher_functions/cipher_text_tables.hpp"
#include "../cipher_functions/cipher_functions.hpp"
#include "./des_key.hpp"


bitset<56> DESKey::contraction_permutation_1(bitset<64> key) {
  bitset<56> permuted_key;
  int i = sizeof(key_P_table) / sizeof(key_P_table[0]) - 1;
  int j = 0;
  while (i >= 0)
  {
    permuted_key[i] = key[key.size() - key_P_table[j]];
    i--;
    j++;
  }
  return permuted_key;
}

bitset<48> DESKey::contraction_permutation_2(bitset<56> key) {
  bitset<48> permuted_key;
  int i = sizeof(key_compression_table) / sizeof(key_compression_table[0]) - 1;
  int j = 0;
  while (i >= 0) {
    permuted_key[i] = key[key.size() - key_compression_table[j]];
    i--;
    j++;
  }
  return permuted_key;
}

bitset<28> DESKey::left_shift(bitset<28> bits, unsigned int shifts) {
  vector<bool> first_bits;
  for (unsigned int i = 0; i < shifts; i++) {
    first_bits.push_back(bits[bits.size() -1 - i]);
  }
  for (unsigned int i = bits.size() - shifts; i > 0; i--)
  {
    bits[i - 1 + shifts] = bits[i - 1];
  }
  for (unsigned int i = 0; i < shifts; i++) {
    bits[shifts - 1 - i] = first_bits[i];
  }
  return bits;
}

vector<bitset<48>> DESKey::get_keys() {

  if (this->keys.size() == this->nr_of_keys) {
    return this->keys;
  }

  bitset<56> permuted_key_1 = this->contraction_permutation_1(initial_key);
  unique_ptr<bitset<28>> left_key_ptr{new bitset<28>(left_part(permuted_key_1))};
  unique_ptr<bitset<28>> right_key_ptr{new bitset<28>(right_part(permuted_key_1))};

  for (unsigned int i = 0; i < this->nr_of_keys; i++) {
    left_key_ptr = make_unique<bitset<28>>(this->left_shift(*left_key_ptr, left_shift_table[i]));
    right_key_ptr = make_unique<bitset<28>>(this->left_shift(*right_key_ptr, left_shift_table[i]));
    this->keys.push_back(this->contraction_permutation_2(concat(*left_key_ptr, *right_key_ptr)));
  }

  return this->keys;
}