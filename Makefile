CXX = g++
CXXFLAGS = -Wall -std=c++20 -Wextra -Wpedantic
CXXDEVFLAGS = -Wall -std=c++20 -Wextra -Wpedantic -g -fsanitize=address
LDFLAGS = -fsanitize=address

SRC=./src/
HEADER=./includes/
IP:= $(host)

s: sender.cpp $(SRC)communicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXFLAGS) -o sender.exe sender.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp && ./sender.exe $(IP)

r: receiver.cpp $(SRC)communicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXFLAGS) -o receiver.exe receiver.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp && ./receiver.exe


dev: senderDev receiverDev
senderDev: sender.cpp $(SRC)communicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXDEVFLAGS) -o sender.exe sender.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp $(LDFLAGS)

receiverDev: receiver.cpp c$(SRC)ommunicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXDEVFLAGS) -o receiver.exe receiver.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp $(LDFLAGS) 

clean:
	rm -f *.exe decoded.txt encoded temp.txt receivedEncoded
