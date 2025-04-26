#include "huffman.hpp"
#include <fstream>

std::map<char, int> Huffman::countOccurences(const char *fileName) {

  std::map<char, int> occurences;

  std::ifstream fileFd(fileName, std::ios::in);
  char ch;
  while (fileFd.get(ch)) {
    occurences[ch]++;
  }

  fileFd.close();

  return occurences;
}
