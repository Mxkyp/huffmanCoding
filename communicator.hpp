#ifndef SENDER_H
#define SENDER_H
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
class Communicator {

public:
  enum Mode { SENDER, RECEIVER };
  Communicator(const int port, Mode mode);
  Communicator(const int port, Mode mode, const char *ipAdress);
  void acceptAnyConnection();
  bool receiveFileFromAnyConnection(std::string fileName);
  std::string receiveStringFromAnyConnection();
  bool sendFileToServer(std::string fileName);
  bool sendStringToServer(std::string str);
  ~Communicator();

private:
  int socketFd;
  int clientSocketFd;
  sockaddr_in address;
  Mode mode;
  void bindOrConnectBasedOn(Mode mode);
};

#endif
