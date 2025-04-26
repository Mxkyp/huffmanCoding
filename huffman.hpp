#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <map>
#include <memory>

struct HuffmanNode {
public:
  HuffmanNode(char character, int frequency)
      : ch(character), freq(frequency), left(nullptr), right(nullptr) {};
  void setLeft(HuffmanNode *ptr);
  void setRight(HuffmanNode *ptr);

private:
  char ch;  // character, or '\0' if it's an internal node
  int freq; // frequency
  std::shared_ptr<HuffmanNode> left;
  std::shared_ptr<HuffmanNode> right;
};

class Huffman {
public:
  enum Mode { BINARY, TEXT };
  std::map<char, int> countOccurences(const char *fileName);
  HuffmanNode createHuffmanTree(std::map<char, int> occurences);

private:
};

#endif
