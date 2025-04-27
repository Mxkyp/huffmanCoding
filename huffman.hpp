#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <map>
#include <memory>
#include <vector>
/**
 * namespace representing the huffman encoding algorithm
 */
namespace Huffman {

/**
 * class representing the HuffmanNode,
 * it holds the char('\0' if not a leaf )
 * the number of its occurences(the sum of occurences of children for vertexes)
 * and pointers to the left and right children
 */
class Node {
public:
  Node(char character, int frequency)
      : ch(character), freq(frequency), left(nullptr), right(nullptr) {};
  void setLeft(std::shared_ptr<Node> ptr);
  void setRight(std::shared_ptr<Node> ptr);
  int getFrequency() const;
  int getCh() const;
  std::shared_ptr<Node> getLeft();
  std::shared_ptr<Node> getRight();

private:
  char ch;  // character, or '\0' if it's an internal node
  int freq; // frequency
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;
};

/**
 * HuffmanComparator to compare the frequency of nodes,
 * needed for finding the two nodes with least occurences
 */
class HuffmanComparator {
public:
  bool operator()(const std::shared_ptr<Node> &a,
                  const std::shared_ptr<Node> &b) {
    return a->getFrequency() > b->getFrequency();
  }
};

/***
 * ALGORITHM METHODS
 */
std::map<char, int> countOccurences(const char *fileName);
std::shared_ptr<Node> createHuffmanTree(std::map<char, int> occurences);
void printTree(const std::shared_ptr<Node> node, int level = 0);
std::map<char, std::string> getHuffmanDict(std::shared_ptr<Node> tree);
void encodeFile(const char *inputFileName, const char *outputFileName,
                std::map<char, std::string> dict);
void decodeFile(const char *inputFileName, const char *outputFileName,
                std::map<std::string, char> dict);
}; // namespace Huffman

#endif
