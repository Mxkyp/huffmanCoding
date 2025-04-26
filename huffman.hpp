#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <map>

class Huffman {
public:
  enum Mode { BINARY, TEXT };
  std::map<char, int> countOccurences(const char *fileName);

private:
};
#endif
