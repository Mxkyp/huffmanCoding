#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <map>
#include <memory>
#include <vector>

/**
 * class representing the HuffmanNode,
 * it holds the char('\0' if not a leaf )
 * the number of its occurences(the sum of occurences of children for vertexes)
 * and pointers to the left and right children
 */
class HuffmanNode {
public:
  HuffmanNode(char character, int frequency)
      : ch(character), freq(frequency), left(nullptr), right(nullptr) {};
  void setLeft(std::shared_ptr<HuffmanNode> ptr);
  void setRight(std::shared_ptr<HuffmanNode> ptr);
  int getFrequency() const;
  int getCh() const;
  std::shared_ptr<HuffmanNode> getLeft();
  std::shared_ptr<HuffmanNode> getRight();

private:
  char ch;  // character, or '\0' if it's an internal node
  int freq; // frequency
  std::shared_ptr<HuffmanNode> left;
  std::shared_ptr<HuffmanNode> right;
};

/**
 * namespace representing the huffman encoding algorithm
 */
namespace Huffman {
std::map<char, int> countOccurences(const char *fileName);
std::shared_ptr<HuffmanNode> createHuffmanTree(std::map<char, int> occurences);
void printTree(const std::shared_ptr<HuffmanNode> node, int level = 0);
void getCharCodes(const std::shared_ptr<HuffmanNode> &node,
                  std::vector<char> buf, std::map<std::string, char> &map);
}; // namespace Huffman

/**
 * HuffmanComparator to compare the frequency of nodes,
 * needed for finding the two nodes with least occurences
 */
class HuffmanComparator {
public:
  bool operator()(const std::shared_ptr<HuffmanNode> &a,
                  const std::shared_ptr<HuffmanNode> &b) {
    return a->getFrequency() > b->getFrequency();
  }
};
#endif
