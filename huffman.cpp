#include "huffman.hpp"
#include <algorithm>
#include <fstream>
#include <memory>
#include <vector>
/**
 * HUFFMAN
 */
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

std::shared_ptr<HuffmanNode>

Huffman::createHuffmanTree(std::map<char, int> occurences) {
  std::vector<std::shared_ptr<HuffmanNode>> trees;
  trees.reserve(occurences.size());

  for (auto &p : occurences) {
    trees.push_back(std::make_shared<HuffmanNode>(p.first, p.second));
  }

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

/**
 * HUFFMAN NODE
 */
int HuffmanNode::getFrequency() const { return freq; }
int HuffmanNode::getCh() const { return ch; }
void HuffmanNode::setLeft(std::shared_ptr<HuffmanNode> ptr) { left = ptr; }
void HuffmanNode::setRight(std::shared_ptr<HuffmanNode> ptr) { right = ptr; }
