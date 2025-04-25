#include "communicator.hpp"

int main(int argc, char *argv[]) {
  Communicator comm(8080, Communicator::Mode::RECEIVER);
  comm.ReceiveFileFromAnyConnection();
  return 0;
}
