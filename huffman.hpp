#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class HuffmanNode {
public:
  HuffmanNode(char character, int frequency)
      : ch(character), freq(frequency), left(nullptr), right(nullptr) {};
  void setLeft(std::shared_ptr<HuffmanNode> ptr);
  void setRight(std::shared_ptr<HuffmanNode> ptr);
  int getFrequency() const;
  int getCh() const;
  static void printTree(const std::shared_ptr<HuffmanNode> node,
                        int level = 0) {
    if (!node)
      return;

    // Print the right subtree (higher levels first)
    printTree(node->right, level + 1);

    // Print the current node with indentation for the current level
    for (int i = 0; i < level; ++i)
      std::cout << "    "; // Indentation
    std::cout << "-> " << node->getCh() << " (" << node->getFrequency()
              << ")\n";

    // Print the left subtree
    printTree(node->left, level + 1);
  }
  static void getCharCodes(const std::shared_ptr<HuffmanNode> &node,
                           std::vector<char> buf,
                           std::map<std::string, char> &map) {
    if (!node) {
      return;
    }

    // If it's a leaf node, insert the code into the map
    if (!node->left && !node->right) {
      std::string code(buf.begin(), buf.end());
      map.insert({code, node->ch});
      return;
    }

    // Traverse right (append 1 for right child)
    buf.push_back('1');
    getCharCodes(node->right, buf, map);
    buf.pop_back();

    // Traverse left (append 0 for left child)
    buf.push_back('0');
    getCharCodes(node->left, buf, map);
    buf.pop_back();
  }

private:
  char ch;  // character, or '\0' if it's an internal node
  int freq; // frequency
  std::shared_ptr<HuffmanNode> left;
  std::shared_ptr<HuffmanNode> right;
};

class Huffman {
public:
  std::map<char, int> countOccurences(const char *fileName);
  std::shared_ptr<HuffmanNode>
  createHuffmanTree(std::map<char, int> occurences);
};

class HuffmanComparator {
public:
  bool operator()(const std::shared_ptr<HuffmanNode> &a,
                  const std::shared_ptr<HuffmanNode> &b) {
    return a->getFrequency() > b->getFrequency();
  }
};
#endif
