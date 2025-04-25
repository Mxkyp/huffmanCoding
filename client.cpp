#include "communicator.hpp"

int main(int argc, char *argv[]) {
  Communicator comm(8080, Communicator::Mode::SENDER);
  comm.sendFileToServer();
  return 0;
}
