#include "huffman.hpp"
#include <iostream>
#include <stdexcept>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw std::runtime_error("Please provide a valid file name");
  }

  Huffman ew;

  std::map<char, int> counted = ew.countOccurences(argv[1]);

  for (auto &p : counted) {
    std::cout << p.first << " " << p.second << std::endl;
  }
}
