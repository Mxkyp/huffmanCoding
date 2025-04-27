#include "communicator.hpp"
#include "huffman.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw std::runtime_error("Please provide a valid IP");
  }
  std::map<char, int> charOccurences = Huffman::countOccurences("test.txt");
  const std::shared_ptr<Huffman::Node> tree =
      Huffman::createHuffmanTree(charOccurences);

  // fake sender
  std::map<char, std::string> charCodes = Huffman::getHuffmanDict(tree);
  std::string dictString = Huffman::dictToString(charCodes);
  Huffman::encodeFile("test.txt", "encoded", charCodes);

  Communicator comm(8080, Communicator::Mode::SENDER, argv[1]);
  std::cout << dictString << std::flush;
  comm.sendStringToServer(dictString);
  sleep(1);
  comm.sendFileToServer("encoded");
  return 0;
}
