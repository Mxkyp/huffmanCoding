#include "huffman.hpp"
#include <iostream>
#include <map>
#include <stdexcept>
#include <utility>
// TODO:: refactor the getCharCodes to return a reversed map,
// wrap the getCharCodes method in another method with the temp vector and map

int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw std::runtime_error("Please provide a valid file name");
  }

  std::map<char, int> charOccurences = Huffman::countOccurences(argv[1]);
  const std::shared_ptr<HuffmanNode> tree =
      Huffman::createHuffmanTree(charOccurences);

  Huffman::printTree(tree);

  std::map<std::string, char> charCodes;
  std::vector<char> vec;

  Huffman::getCharCodes(tree, vec, charCodes);

  // Print the Huffman codes
  for (std::pair<std::string, char> p : charCodes) {
    std::cout << p.first << " lol: " << (int)p.second << " " << p.second
              << std::endl;
  }
}
