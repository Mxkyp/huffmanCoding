CXX = g++
CXXFLAGS = -Wall -std=c++20 -Wextra -Wpedantic
CXXDEVFLAGS = -Wall -std=c++20 -Wextra -Wpedantic -g -fsanitize=address
LDFLAGS = -fsanitize=address

all: sender receiver
sender: sender.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXFLAGS) -o sender.exe sender.cpp communicator.cpp

receiver: receiver.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXFLAGS) -o receiver.exe receiver.cpp communicator.cpp

dev: senderDev receiverDev
senderDev: sender.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXDEVFLAGS) -o sender.exe sender.cpp communicator.cpp $(LDFLAGS)

receiverDev: receiver.cpp communicator.cpp communicator.hpp
	$(CXX) $(CXXDEVFLAGS) -o receiver.exe receiver.cpp communicator.cpp $(LDFLAGS) 

testH: testRun

testRun: test.cpp huffman.cpp huffman.hpp
	$(CXX) $(CXXDEVFLAGS) -o test.exe test.cpp huffman.cpp $(LDFLAGS)

clean:
	rm -f *.exe
