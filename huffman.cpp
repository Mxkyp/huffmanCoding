#include "huffman.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace Huffman {
std::map<char, int> countOccurences(const char *fileName) {

  std::map<char, int> occurences;

  std::ifstream fileFd(fileName, std::ios::in);
  char ch;
  while (fileFd.get(ch)) {
    occurences[ch]++;
  }

  fileFd.close();

  return occurences;
}

std::shared_ptr<HuffmanNode> createHuffmanTree(std::map<char, int> occurences) {
  std::vector<std::shared_ptr<HuffmanNode>> trees;
  trees.reserve(occurences.size());

  // create Pairs of chars and occurences
  for (auto &p : occurences) {
    trees.push_back(std::make_shared<HuffmanNode>(p.first, p.second));
  }

  // combine the pairs with least occurences until only one tree remains
  while (trees.size() > 1) {
    std::sort(trees.begin(), trees.end(), HuffmanComparator());

    auto last = trees.back();
    trees.pop_back();

    auto secondLast = trees.back();
    trees.pop_back();

    auto parent = std::make_shared<HuffmanNode>(
        '\0', last->getFrequency() + secondLast->getFrequency());
    parent->setLeft(secondLast);
    parent->setRight(last);
    trees.push_back(parent);
  }

  return trees.front();
}

void printTree(const std::shared_ptr<HuffmanNode> node, int level) {
  if (!node)
    return;

  // Print the right subtree (higher levels first)
  printTree(node->getRight(), level + 1);

  // Print the current node with indentation for the current level
  for (int i = 0; i < level; ++i)
    std::cout << "    "; // Indentation
  std::cout << "-> " << node->getCh() << " (" << node->getFrequency() << ")\n";

  // Print the left subtree
  printTree(node->getLeft(), level + 1);
}

/**
 * modify the map param so it stores the huffman dictionary,
 * based on the root node
 */
void getCharCodes(const std::shared_ptr<HuffmanNode> &node,
                  std::vector<char> buf, std::map<std::string, char> &map) {
  if (!node) {
    return;
  }

  // If it's a leaf node, insert the code into the map
  if (!node->getLeft() && !node->getRight()) {
    std::string code(buf.begin(), buf.end());
    map.insert({code, node->getCh()});
    return;
  }

  // Traverse right (append 1 for right child)
  buf.push_back('1');
  getCharCodes(node->getRight(), buf, map);
  buf.pop_back();

  // Traverse left (append 0 for left child)
  buf.push_back('0');
  getCharCodes(node->getLeft(), buf, map);
  buf.pop_back();
}
} // namespace Huffman

/**
 * HUFFMAN NODE
 */
int HuffmanNode::getFrequency() const { return freq; }
int HuffmanNode::getCh() const { return ch; }
void HuffmanNode::setLeft(std::shared_ptr<HuffmanNode> ptr) { left = ptr; }
void HuffmanNode::setRight(std::shared_ptr<HuffmanNode> ptr) { right = ptr; }
std::shared_ptr<HuffmanNode> HuffmanNode::getLeft() { return left; }
std::shared_ptr<HuffmanNode> HuffmanNode::getRight() { return right; }
