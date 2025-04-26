#include "huffman.hpp"
#include <iostream>
#include <map>
#include <stdexcept>
#include <utility>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw std::runtime_error("Please provide a valid file name");
  }

  std::map<char, int> counted = Huffman::countOccurences(argv[1]);
  const std::shared_ptr<HuffmanNode> tree = Huffman::createHuffmanTree(counted);

  Huffman::printTree(tree);

  std::map<std::string, char> map;
  std::vector<char> vec;

  Huffman::getCharCodes(tree, vec, map);

  // Print the Huffman codes
  for (std::pair<std::string, char> p : map) {
    std::cout << p.first << " lol: " << (int)p.second << " " << p.second
              << std::endl;
  }
}
