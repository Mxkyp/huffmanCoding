#include "../includes/communicator.hpp"
#include <cstring>
#include <fstream>
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

void Communicator::acceptAnyConnection() {
  listen(socketFd, 5);
  clientSocketFd = accept(socketFd, nullptr, nullptr);
}

// Close the socket
Communicator::~Communicator() { close(socketFd); }

bool Communicator::receiveFileFromAnyConnection(std::string fileName) {
  if (mode == SENDER) {
    throw std::runtime_error("Mode not RECEIVER");
  }

  // Open the file to save received data
  std::ofstream outFile(fileName, std::ios::binary);
  if (!outFile.is_open()) {
    throw std::runtime_error("Failed to open output file");
  }

  char buffer[1024] = {0}; // Buffer for receiving data
  ssize_t bytesRead;

  while ((bytesRead = recv(clientSocketFd, buffer, sizeof(buffer), 0)) > 0) {
    outFile.write(buffer, bytesRead); // Write received data to file
    if (bytesRead < sizeof(buffer)) {
      break; // Break if the message is fully received
    }
  }

  if (bytesRead < 0) {
    std::cerr << "Error in receiving file data" << std::endl;
  }

  // Close the file and socket
  outFile.close();

  return true;
}

std::string Communicator::receiveStringFromAnyConnection() {
  if (mode == SENDER) {
    throw std::runtime_error("Mode not RECEIVER");
  }

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

void Communicator::sendStringToServer(std::string str) {
  if (this->mode == RECEIVER) {
    std::cout << "IGET HERE!" << std::endl;
    throw std::runtime_error("Mode not SENDER");
  }
  send(socketFd, str.c_str(), str.length(), 0);
}

bool Communicator::sendFileToServer(std::string fileName) {
  if (this->mode == RECEIVER) {
    std::cout << "IGET HERE!" << std::endl;
    throw std::runtime_error("Mode not SENDER");
  }
  std::ifstream file(fileName, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }

  const size_t bufferSize = 4096; // 4 KB chunks
  char buffer[bufferSize];

  while (file.good()) {
    file.read(buffer, bufferSize);
    std::streamsize bytesRead =
        file.gcount(); // how many bytes were actually read

    if (bytesRead > 0) {
      int bytesSent = send(socketFd, buffer, bytesRead, 0);
      if (bytesSent < 0) {
        file.close();
        throw std::runtime_error("Failed to send file data");
      }
    }
  }

  file.close();
  return true;
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
