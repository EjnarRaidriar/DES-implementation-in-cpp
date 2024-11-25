#ifndef FUNC_HPP
#define FUNC_HPP

#include <iostream>
#include <string>

const std::string UPPERCASE_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool is_hex(std::string input);

std::string replace(std::string text, char old_ch, char new_ch);

#endif