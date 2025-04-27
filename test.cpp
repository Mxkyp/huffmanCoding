#include "communicator.hpp"
#include "huffman.hpp"
#include <iostream>
#include <map>
#include <stdexcept>
#include <utility>
// TODO:: refactor the getCharCodes to return a reversed map,
// wrap the getCharCodes method in another method with the temp vector and map

/**
 * turn the dict to string for sending over a network
 */
std::string dictToString(std::map<char, std::string> dict);

/**
 * receive the dictonary from the network and turn it back to a map
 */
std::map<std::string, char> stringToDict(std::string str);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw std::runtime_error("Please provide a valid file name");
  }

  std::map<char, int> charOccurences = Huffman::countOccurences(argv[1]);
  const std::shared_ptr<Huffman::Node> tree =
      Huffman::createHuffmanTree(charOccurences);

  // Huffman::printTree(tree);

  // fake sender
  std::map<char, std::string> charCodes = Huffman::getHuffmanDict(tree);
  Huffman::encodeFile(argv[1], "encoded", charCodes);

  std::string dictString = dictToString(charCodes);

  // fake receiver
  /*
  std::map<std::string, char> dict = stringToDict(dictString);
  Huffman::decodeFile("./encoded.txt", "decoded.txt", dict);
  */
}

/**
 * format the dictionary to be send over a network,
 * the format is 'Char'Code'Char'Code' where '''' marks the end of the
 * dictionary
 */
std::string dictToString(std::map<char, std::string> dict) {
  std::string str;

  for (const auto &p : dict) {
    str += '\'';
    str += p.first;
    str += '\'';
    str += p.second;
  }
  str += "\'\'\'\'";

  return str;
}

/***
 * read the dictionary from the network ino a map
 */
std::map<std::string, char> stringToDict(std::string str) {
  std::map<std::string, char> dict;
  std::string charCode;
  char currentChar;

  for (int i = 0; i < str.length();) {
    if (str.at(i) == '\'' && str.at(i + 1) == '\'' && str.at(i + 2) == '\'' &&
        str.at(i + 3) == '\'') {
      break;
    } else if (str.at(i) == '\'' && str.at(i + 1) == '\'' &&
               str.at(i + 2) == '\'' && str.at(i + 3) != '\'') {
      currentChar = '\'';
      i += 3;
      while (str.at(i) != '\'') {
        charCode += str.at(i);
      }
    } else if (str.at(i) == '\'' && str.at(i + 1) != '\'' &&
               str.at(i + 2) == '\'' && str.at(i + 3) != '\'') {
      i += 1;
      currentChar = str.at(i);
      i += 2;
      while (str.at(i) != '\'') {
        charCode += str.at(i);
        i++;
      }
    }
    dict.insert(std::make_pair(charCode, currentChar));
    charCode.clear();
  }

  return dict;
}
