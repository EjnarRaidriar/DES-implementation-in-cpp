#include "./des.hpp"
#include "../cipher_functions/cipher_text_tables.hpp"
#include "../cipher_functions/cipher_functions.hpp"

#include <vector>
#include <memory>
#include <algorithm>

bitset<48> DES::expansion_permutation(bitset<32> bits) {
  bitset<48> expanded_bits;
  for (unsigned int i = expanded_bits.size(); i > 0; i--) {
    expanded_bits[i - 1] = bits[bits.size() - EF_table[expanded_bits.size() - i]];
  }
  return expanded_bits;
}

bitset<6> DES::subbits(unsigned int nr, bitset<48> bits) {
  bitset<6> split_bits;
  for (unsigned int i = split_bits.size(); i > 0; i--) {
    split_bits[i - 1] = bits[bits.size() - (nr - 1) * split_bits.size() - 1 - split_bits.size() + i];
  }
  return split_bits;
}

bitset<4> DES::s_box_substitution(unsigned int nr, bitset<6> bits) {
  unsigned int row_int;
  unsigned int column_int;
  {
    bitset<2> row;
    row[0] = bits[0];
    row[1] = bits[5];
    bitset<4> column;
    column[0] = bits[1];
    column[1] = bits[2];
    column[2] = bits[3];
    column[3] = bits[4];
    row_int = row.to_ullong();
    column_int = column.to_ullong();
  }
  bitset<4> result = S_boxes[nr - 1][row_int][column_int];
  return result;
}

bitset<32> DES::s_box(bitset<48> bits) {
  bitset<4> s[8];
  for (unsigned int i = 0; i < 8; i++) {
    this->output_file << "Bits for S" << i + 1 << ": ";
    bitset<6> temp = this->subbits(i + 1, bits);
    this->output_file << temp << " : ";
    s[i] = this->s_box_substitution(i + 1, temp);
    this->output_file << "S" << i + 1 << " = " << s[i] << endl;
  }
  bitset<16> left_bits = concat(s[0], concat(s[1], concat(s[2], s[3])));
  return concat(left_bits, concat(s[4], concat(s[5], concat(s[6], s[7]))));
}

bitset<32> DES::f_function(bitset<32> bits, bitset<48> key) {
  bitset<48> expanded_bits = this->expansion_permutation(bits);
  this->output_file << "E(R) = " << expanded_bits << endl;
  expanded_bits ^= key;
  this->output_file << "E xor K = " << expanded_bits << endl;
  bits = this->s_box(expanded_bits);
  this->output_file << "S(E xor K) = " << bits << endl;
  bits = permutation(bits, P_table);
  return bits;
}

bitset<64> DES::encryption_decryption_function(string message, vector<bitset<48>> keys) {
  bitset<64> message_bits = (bitset<64>)message;
  this->output_file << "Initial message:" << endl
                    << message_bits << endl;
  message_bits = permutation(message_bits, IP_table);
  this->output_file << "Initial Permutation:" << endl
                    << message_bits << endl;

  unique_ptr<bitset<32>> left_part_ptr{new bitset<32>(left_part(message_bits))};
  unique_ptr<bitset<32>> right_part_ptr{new bitset<32>(right_part(message_bits))};

  this->output_file << "L0 = " << *left_part_ptr << endl;
  this->output_file << "R0 = " << *right_part_ptr << endl << endl;

  for (unsigned int i = 0; i < keys.size(); i++) {
    this->output_file << "Round " << i + 1 << endl;
    this->output_file << "R" << i << " = " << *right_part_ptr << endl;
    this->output_file << "K" << i + 1 << " = " << keys[i] << endl;
    bitset<32> new_right_part = *left_part_ptr ^ this->f_function(*right_part_ptr, keys[i]);
    left_part_ptr = make_unique<bitset<32>>(*right_part_ptr);
    right_part_ptr = make_unique<bitset<32>>(new_right_part);
    this->output_file << "L" << i + 1 << " = " << "R" << i << " = " << *left_part_ptr << endl;
    this->output_file << "R" << i + 1 << " = F = P(S(E xor K)) = " << *right_part_ptr << endl << endl;
  }
  bitset<64> result = permutation(concat(*right_part_ptr, *left_part_ptr), FP_table);
  this->output_file << "Result:" << endl
                    << result << endl;
  return result;
}

bitset<64> DES::encrypt(string message) {
  vector<bitset<48>> keys = this->key.get_keys();
  this->output_file << "Encryption: " << endl << endl;
  return this->encryption_decryption_function(message, keys);
}

bitset<64> DES::decrypt(string message) {
  vector<bitset<48>> keys = this->key.get_keys();
  reverse(keys.begin(), keys.end());
  this->output_file << "Decryption: " << endl;
  this->output_file << "(keys' order is reversed)" << endl << endl;
  return this->encryption_decryption_function(message, keys);
}