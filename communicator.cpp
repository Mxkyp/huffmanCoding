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

// Close the socket
Communicator::~Communicator() { close(socketFd); }

bool Communicator::receiveFileFromAnyConnection(std::string fileName) {
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

std::string Communicator::receiveStringFromAnyConnection() {
  if (mode == SENDER) {
    throw std::runtime_error("Mode not RECEIVER");
  }

  listen(socketFd, 5);
  int clientSocketFd = accept(socketFd, nullptr, nullptr);

  char buffer[10 * 1024] = {0}; // Buffer to store received data
  std::string receivedString;
  ssize_t bytesRead;

  while ((bytesRead = recv(clientSocketFd, buffer, sizeof(buffer), 0)) > 0) {
    receivedString.append(buffer, bytesRead);
    if (bytesRead < sizeof(buffer)) {
      break; // Break if the message is fully received
    }
  }

  if (bytesRead < 0) {
    throw std::runtime_error("Failed to receive data");
  }

  return receivedString;
}

bool Communicator::sendStringToServer(std::string str) {
  if (this->mode == RECEIVER) {
    std::cout << "IGET HERE!" << std::endl;
    throw std::runtime_error("Mode not SENDER");
  }
  long result = send(socketFd, str.c_str(), str.length(), 0);
}

bool Communicator::sendFileToServer(std::string fileName) {
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
