#include "communicator.hpp"
#include "huffman.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Communicator comm(8080, Communicator::Mode::RECEIVER);

  std::string dictString = comm.receiveStringFromAnyConnection();
  std::cout << dictString << std::flush;
  std::map<std::string, char> dict = Huffman::stringToDict(dictString);
  comm.receiveFileFromAnyConnection("encoded1");
  Huffman::decodeFile("encoded1", "decoded.txt", dict);
  return 0;
}
