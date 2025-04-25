#include "sender.hpp"
#include <iostream>

Sender::Sender(const int port) {
  address.sin_family = AF_INET;
  address.sin_port =
      htons(port); // convert from machine byte order to network byte order
  address.sin_addr.s_addr = INADDR_ANY; // bind to any address
  if (bind(socket, (struct sockaddr *)&address, sizeof(address)) != 0) {
    throw new std::runtime_error("Bind error");
  }
}
