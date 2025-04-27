#include "./includes/communicator.hpp"
#include "./includes/huffman.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Communicator comm(8080, Communicator::Mode::RECEIVER);

  comm.acceptAnyConnection();

  std::string dictString = comm.receiveStringFromAnyConnection();
  std::cout << dictString << std::flush;
  std::map<std::string, char> dict = Huffman::stringToDict(dictString);

  comm.receiveFileFromAnyConnection("receivedEncoded");
  Huffman::decodeFile("receivedEncoded", "decoded.txt", dict);
  return 0;
}
