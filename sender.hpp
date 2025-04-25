#ifndef SENDER_H
#define SENDER_H
#include <arpa/inet.h>
#include <unistd.h>

class Sender {

private:
  int socket;
  sockaddr_in address;

public:
  Sender(int port);
  ~Sender();
};

#endif
