#include "communicator.hpp"
#include <stdexcept>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw std::runtime_error("Please provide a valid IP");
  }
  Communicator comm(8080, Communicator::Mode::SENDER, argv[1]);
  comm.sendFileToServer();
  return 0;
}
