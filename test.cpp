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
  const std::shared_ptr<Huffman::Node> tree =
      Huffman::createHuffmanTree(charOccurences);

  Huffman::printTree(tree);

  std::map<char, std::string> charCodes = Huffman::getHuffmanDict(tree);

  // Print the Huffman codes
  for (std::pair<char, std::string> p : charCodes) {
    std::cout << p.first << " lol: " << (int)p.first << " " << p.second
              << std::endl;
  }
}
