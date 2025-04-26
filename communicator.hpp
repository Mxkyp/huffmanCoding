#ifndef SENDER_H
#define SENDER_H
#include <arpa/inet.h>
#include <unistd.h>

class Communicator {

public:
  enum Mode { SENDER, RECEIVER };
  Communicator(const int port, Mode mode);
  Communicator(const int port, Mode mode, const char *ipAdress);
  bool ReceiveFileFromAnyConnection();
  bool sendFileToServer();
  ~Communicator();

private:
  int socketFd;
  sockaddr_in address;
  Mode mode;
  void bindOrConnectBasedOn(Mode mode);
};

#endif
