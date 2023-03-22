#include "inputData.h"
#include "CYK.h"

void inputData::getTransitions() {
  while (!fin.eof()) {
    std::string line;
    std::getline(fin, line);

    std::istringstream iss(line);
    char from;
    iss >> from;
    std::string dummyStr;
    iss >> dummyStr;
    std::string to;
    while (iss >> to) {
      if (to.size() == 2) {
        cyk->toNonTerminal[from].push_back(std::pair(to[0], to[1]));
      } else if (to.size() == 1) {
        if (to[0] != '|') {
          cyk->toTerminal[from].insert(to[0]);
        }
      }
    }
  }
  cyk->_state_cnt = cyk->toNonTerminal.size();
}

void inputData::getCYK() {
  std::string pathToInputFile = "../" + inputFileName;
  fin.open(pathToInputFile);
  getTransitions();
//  for (auto el: cyk->toTerminal) {
//    std::cout << el.first << ": ";
//    for (auto t: el.second) {
//      std::cout << t << ' ';
//    }
//    std::cout << '\n';
//  }
//  for (auto el: cyk->toNonTerminal) {
//    std::cout << el.first << ": ";
//    for (auto t: el.second) {
//      std::cout << t.first << t.second << ' ';
//    }
//    std::cout << '\n';
//  }
  fin.close();
}
