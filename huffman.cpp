#include "huffman.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sys/types.h>
#include <vector>

namespace Huffman {
/**
 * NODE
 */
int Node::getFrequency() const { return freq; }
int Node::getCh() const { return ch; }
void Node::setLeft(std::shared_ptr<Node> ptr) { left = ptr; }
void Node::setRight(std::shared_ptr<Node> ptr) { right = ptr; }
std::shared_ptr<Node> Node::getLeft() { return left; }
std::shared_ptr<Node> Node::getRight() { return right; }

/**
 * ALGORITHM METHODS
 */

/**
 * NOT EXPORTED modify the map param so it stores the huffman dictionary,
 * based on the root node
 */
void getCharCodes(const std::shared_ptr<Node> &node, std::vector<char> buf,
                  std::map<char, std::string> &map) {
  if (!node) {
    return;
  }

  // If it's a leaf node, insert the code into the map
  if (!node->getLeft() && !node->getRight()) {
    std::string code(buf.begin(), buf.end());
    map.insert({node->getCh(), code});
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

/**
 * get the huffman dictionary
 */
std::map<char, std::string> getHuffmanDict(std::shared_ptr<Node> tree) {
  std::map<char, std::string> dict;
  std::vector<char> vec;
  getCharCodes(tree, vec, dict);

  return dict;
}

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

std::shared_ptr<Node> createHuffmanTree(std::map<char, int> occurences) {
  std::vector<std::shared_ptr<Node>> trees;
  trees.reserve(occurences.size());

  // create Pairs of chars and occurences
  for (auto &p : occurences) {
    trees.push_back(std::make_shared<Node>(p.first, p.second));
  }

  // combine the pairs with least occurences until only one tree remains
  while (trees.size() > 1) {
    std::sort(trees.begin(), trees.end(), HuffmanComparator());

    auto last = trees.back();
    trees.pop_back();

    auto secondLast = trees.back();
    trees.pop_back();

    auto parent = std::make_shared<Node>('\0', last->getFrequency() +
                                                   secondLast->getFrequency());
    parent->setLeft(secondLast);
    parent->setRight(last);
    trees.push_back(parent);
  }

  return trees.front();
}

void printTree(const std::shared_ptr<Node> node, int level) {
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

void encodeFile(const char *inputFileName, const char *outputFileName,
                std::map<char, std::string> dict) {

  std::ifstream uncodedFd(inputFileName, std::ios::in);
  std::fstream tempFd("temp.txt", std::ios::out);
  std::ofstream trullycodedFd(outputFileName, std::ios::out | std::ios::binary);

  char ch;
  long long encodedBitSize = 0;

  while (uncodedFd.get(ch)) {
    encodedBitSize += dict[ch].length();
    tempFd << dict[ch];
  }
  tempFd.close();

  char paddingBitsNeeded = 8 - (encodedBitSize % 8);
  trullycodedFd.write(&paddingBitsNeeded, 1);
  std::string currentByte(paddingBitsNeeded, '0');

  tempFd.open("temp.txt", std::ios::in);

  while (tempFd.get(ch)) {
    currentByte += ch;

    if (currentByte.length() == 8) {
      char parsed = static_cast<char>(strtol(currentByte.c_str(), nullptr, 2));
      trullycodedFd << parsed;
      currentByte.clear();
    }
  }
  trullycodedFd.close();
  uncodedFd.close();
  tempFd.close();
}

void decodeFile(const char *inputFileName, const char *outputFileName,
                std::map<std::string, char> dict) {
  std::ifstream codedFd(inputFileName, std::ios::in | std::ios::binary);
  std::ofstream uncodedFd(outputFileName, std::ios::out);
  char ch;
  std::string code;

  char paddingBits = codedFd.get();
  std::string recoveredBits;
  codedFd.get(ch);

  for (int i = 7 - paddingBits; i >= 0; --i) {
    recoveredBits += extractBitValueFrom(ch, i);
    if (dict.find(recoveredBits) != dict.end()) {
      uncodedFd << dict[recoveredBits];
      recoveredBits.clear();
    }
  }

  while (codedFd.get(ch)) {
    for (int i = 7; i >= 0; --i) {
      recoveredBits += extractBitValueFrom(ch, i);
      if (dict.find(recoveredBits) != dict.end()) {
        uncodedFd << dict[recoveredBits];
        recoveredBits.clear();
      }
    }
  }

  uncodedFd.close();
  codedFd.close();
}

char extractBitValueFrom(char ch, int i) { return ((ch >> i) & 1) ? '1' : '0'; }

} // namespace Huffman
