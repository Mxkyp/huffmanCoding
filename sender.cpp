#include "communicator.hpp"

int main(void) {
  Communicator comm(8080, Communicator::Mode::SENDER);
  comm.sendFileToServer();
  return 0;
}
