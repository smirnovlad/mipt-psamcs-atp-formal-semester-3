#include <iostream>
#include <fstream>

class NFA;

#ifndef INPUT_DATA_H_INCLUDED
#define INPUT_DATA_H_INCLUDED

class input_data {
 private:
  NFA* FNA;
  std::string input_file_name;
  std::ifstream fin;

  std::string get_doa_version();
  uint32_t get_start_id();
  void get_acceptance();
  void get_transitions();
  void update_state_cnt(uint32_t state_id);
 public:
  input_data(const std::string& input_file_name, NFA* FNA) :
      input_file_name(input_file_name), FNA(FNA) {}

  void get();
};

#endif