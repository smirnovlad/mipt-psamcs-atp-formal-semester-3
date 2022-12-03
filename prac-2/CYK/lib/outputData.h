#include <iostream>
#include <fstream>
#include <vector>

class CYK;

#ifndef OUTPUT_DATA_H_INCLUDED
#define OUTPUT_DATA_H_INCLUDED

class outputData {
 private:
  CYK *cyk;
  std::string output_file_name;
  std::ofstream fout;
  std::ifstream fin;

 public:
  outputData(const std::string &output_file_name, CYK *cyk) :
      output_file_name(output_file_name), cyk(cyk) {}

  void put(const std::vector<bool> &res);
};

#endif