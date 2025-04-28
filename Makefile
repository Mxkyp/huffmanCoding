CXX = g++
CXXFLAGS = -w -std=c++20 
CXXDEVFLAGS = -Wall -std=c++20 -Wextra -Wpedantic -g -fsanitize=address
LDFLAGS = -fsanitize=address

SRC=./src/
HEADER=./includes/
IP:= $(ip)
HORIZONTAL_LINE=printf '%.0s-' $$(seq 1 10)
PRINT_ENCODED=$(NEWLINE) && $(HORIZONTAL_LINE) && $(NEWLINE) && echo ENCODED: && $(HORIZONTAL_LINE) && $(NEWLINE) && cat receivedEncoded
PRINT_DECODED=$(NEWLINE) && $(HORIZONTAL_LINE) && $(NEWLINE) && echo DECODED: && $(HORIZONTAL_LINE) && $(NEWLINE) && cat decoded.txt
NEWLINE=printf '\n'

s: sender.cpp $(SRC)communicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXFLAGS) -o sender.exe sender.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp && ./sender.exe $(IP)

r: receiver.cpp $(SRC)communicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXFLAGS) -o receiver.exe receiver.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp && ./receiver.exe \
	&& $(PRINT_ENCODED) && $(PRINT_DECODED)

sDev: sender.cpp $(SRC)communicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXDEVFLAGS) -o sender.exe sender.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp $(LDFLAGS) && ./sender.exe $(IP)

rDev: receiver.cpp $(SRC)communicator.cpp $(HEADER)communicator.hpp $(SRC)huffman.cpp $(HEADER)huffman.hpp
	$(CXX) $(CXXDEVFLAGS) -o receiver.exe receiver.cpp $(SRC)communicator.cpp $(SRC)huffman.cpp $(LDFLAGS) && ./receiver.exe

clean:
	rm -f *.exe decoded.txt encoded temp.txt receivedEncoded
