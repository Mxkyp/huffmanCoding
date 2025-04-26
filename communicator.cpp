#include "communicator.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>

// a constructor for serial connections
Communicator::Communicator(const int port, Mode mode) {
  socketFd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFd < 0) {
    throw std::runtime_error("Socket creation failed");
  }
  address.sin_family = AF_INET;
  address.sin_port =
      htons(port); // convert from machine byte order to network byte order
  address.sin_addr.s_addr = INADDR_ANY; // bind to any address
  bindOrConnectBasedOn(mode);
}

// a constructor for local network connections
Communicator::Communicator(const int port, Mode mode, const char *ipAdress) {
  socketFd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFd < 0) {
    throw std::runtime_error("Socket creation failed");
  }
  address.sin_family = AF_INET;
  address.sin_port =
      htons(port); // convert from machine byte order to network byte order
  address.sin_addr.s_addr = INADDR_ANY; // bind to any address
  inet_pton(AF_INET, ipAdress, &address.sin_addr);
  bindOrConnectBasedOn(mode);
}

Communicator::~Communicator() { close(socketFd); }

bool Communicator::ReceiveFileFromAnyConnection() {
  if (mode == SENDER) {
    throw std::runtime_error("Mode not RECEIVER");
  }
  listen(socketFd, 5);
  int clientsocketFd = accept(socketFd, nullptr, nullptr);

  // recieving data
  char buffer[1024] = {0};
  recv(clientsocketFd, buffer, sizeof(buffer), 0);
  std::cout << "Message from client: " << buffer << std::endl;

  return true;
}

bool Communicator::sendFileToServer() {
  if (this->mode == RECEIVER) {
    std::cout << "IGET HERE!" << std::endl;
    throw std::runtime_error("Mode not SENDER");
  }
  const char *message = "Hello, server!";
  int result = send(socketFd, message, strlen(message), 0);
}

void Communicator::bindOrConnectBasedOn(Mode mode) {
  this->mode = mode;

  if (this->mode == RECEIVER) {
    if (bind(socketFd, (struct sockaddr *)&address, sizeof(address)) != 0) {
      throw std::runtime_error("Bind error");
    }
  } else if (this->mode == SENDER) {
    if (connect(socketFd, (struct sockaddr *)&address, sizeof(address)) != 0) {
      throw std::runtime_error("connection error");
    }
  }
}
