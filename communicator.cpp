#include "communicator.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>

Communicator::Communicator(const int port, Mode mode) {
  address.sin_family = AF_INET;
  address.sin_port =
      htons(port); // convert from machine byte order to network byte order
  address.sin_addr.s_addr = INADDR_ANY; // bind to any address
  bindOrConnectBasedOn(mode);
}

Communicator::~Communicator() { close(socket); }

bool Communicator::ReceiveFileFromAnyConnection() {
  if (mode == SENDER) {
    throw new std::runtime_error("Mode not RECEIVER");
  }
  listen(socket, 5);
  int clientSocket = accept(socket, nullptr, nullptr);

  // recieving data
  char buffer[1024] = {0};
  recv(clientSocket, buffer, sizeof(buffer), 0);
  std::cout << "Message from client: " << buffer << std::endl;

  return true;
}

bool Communicator::sendFileToServer() {
  if (mode == RECEIVER) {
    throw new std::runtime_error("Mode not SENDER");
  }
  const char *message = "Hello, server!";
  send(socket, message, strlen(message), 0);
}

void Communicator::bindOrConnectBasedOn(Mode mode) {
  this->mode = mode;

  if (this->mode == RECEIVER) {
    if (bind(socket, (struct sockaddr *)&address, sizeof(address)) != 0) {
      throw new std::runtime_error("Bind error");
    }
  } else if (this->mode == SENDER) {
    if (connect(socket, (struct sockaddr *)&address, sizeof(address)) != 0) {
      throw new std::runtime_error("connection error");
    }
  }
}
