#include <iostream>
#include <fstream>

class CYK;

#ifndef INPUT_DATA_H_INCLUDED
#define INPUT_DATA_H_INCLUDED

class inputData {
 private:
  CYK *cyk;
  std::string inputFileName;
  std::ifstream fin;

  void getTransitions();
 public:
  inputData(const std::string &inputFileName,
            CYK *cyk) :
      inputFileName(inputFileName),
      cyk(cyk) {}

  void getCYK();
};

#endif