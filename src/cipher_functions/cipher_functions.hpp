#ifndef CIPHER_TEXT_FUNCTIONS_HPP
#define CIPHER_TEXT_FUNCTIONS_HPP

#include <iostream>
#include <bitset>

template<size_t N>
std::bitset<N / 2> left_part(std::bitset<N> bits) {
  std::bitset<N / 2> left_half;
  for (unsigned int i = bits.size() - 1; i >= bits.size() / 2; i--) {
    left_half[i - (N / 2)] = bits[i];
  }
  return left_half;
}

template<size_t N>
std::bitset<N / 2> right_part(std::bitset<N> bits) {
  std::bitset<N / 2> right_half;
  for (unsigned int i = right_half.size(); i > 0; i--) {
    right_half[i-1] = bits[i-1];
  }
  return right_half;
}

template <size_t N1, size_t N2>
std::bitset<N1 + N2> concat(std::bitset<N1> b1, std::bitset<N2> b2) {
  std::bitset<N1 + N2> bits;
  for (unsigned int i = 0; i < N2; i++) {
    bits[i] = b2[i];
  }
  for (unsigned int i = 0; i < N1; i++) {
    bits[i + b2.size()] = b1[i];
  }
  return bits;
}

template <size_t N>
std::bitset<N> permutation(std::bitset<N> bits, const int *table) {
  std::bitset<N> new_bits;
  for (unsigned int i = bits.size(); i > 0; i--) {
    new_bits[i - 1] = bits[bits.size() - table[bits.size() - i]];
  }
  return new_bits;
}

#endif