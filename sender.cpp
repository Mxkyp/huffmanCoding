#include "communicator.hpp"

int main(int argc, char *argv[]) {
  Communicator comm(8080, Communicator::Mode::SENDER, "192.168.100.202");
  comm.sendFileToServer();
  return 0;
}
