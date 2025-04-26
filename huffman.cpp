#include "huffman.hpp"
#include <fstream>
#include <vector>

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

HuffmanNode createHuffmanTree(std::map<char, int> occurences) {
  std::vector<HuffmanNode> trees;
  trees.reserve(occurences.size());

  for (auto &p : occurences) {
    trees.push_back(HuffmanNode(p.first, p.second));
  }
}
