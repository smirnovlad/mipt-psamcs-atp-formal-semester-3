#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include "inputData.h"
#include "outputData.h"

#ifndef CYK_H_INCLUDED
#define CYK_H_INCLUDED

class CYK {
 protected:
  using Transitions = std::vector<std::pair<char, char>>;

  char startSymbol = 'S';
  char epsSymbol = '#';
  uint32_t _state_cnt = 0;
  std::map<char, Transitions> toNonTerminal;
  std::map<char, std::set<char>> toTerminal;

  void getCYK(const std::string &inputFileName);

  friend class inputData;
  friend class outputData;

 public:
  CYK(const std::string &inputFileName) {
    getCYK(inputFileName);
  }

  CYK(const CYK &other) = default;

  void recognize(const std::string &toRecognizeFileName,
                 const std::string &outputFileName);
};

#endif