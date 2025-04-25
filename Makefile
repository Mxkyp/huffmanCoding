CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic
CXXDEVFLAGS = -Wall -Wextra -Wpedantic -g -fsanitize=address
LDFLAGS = -fsanitize=address

all: sender receiver
sender: sender.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXFLAGS) -o sender sender.cpp communicator.cpp

receiver: receiver.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXFLAGS) -o receiver receiver.cpp communicator.cpp

dev: senderDev receiverDev
senderDev: sender.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXDEVFLAGS) -o sender sender.cpp communicator.cpp $(LDFLAGS)

receiverDev: receiver.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXDEVFLAGS) -o receiver receiver.cpp communicator.cpp $(LDFLAGS) 

clean:
	rm -f sender receiver
