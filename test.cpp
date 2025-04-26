#include "huffman.hpp"
#include <map>
#include <stdexcept>
#include <utility>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw std::runtime_error("Please provide a valid file name");
  }

  Huffman ew;

  std::map<char, int> counted = ew.countOccurences(argv[1]);

  const std::shared_ptr<HuffmanNode> tree = ew.createHuffmanTree(counted);
  HuffmanNode::printTree(tree);

  std::map<std::string, char> map;
  std::vector<char> vec;

  // Generate Huffman codes
  HuffmanNode::getCharCodes(tree, vec, map);

  // Print the Huffman codes
  for (std::pair<std::string, char> p : map) {
    if (p.first == "000") {
      std::cout << "good";
    }
    std::cout << p.first << " lol: " << (int)p.second << " " << p.second
              << std::endl;
  }
}
