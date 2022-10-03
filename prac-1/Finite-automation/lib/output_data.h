#include <iostream>
#include <fstream>

class NFA;

class output_data {
 private:
  NFA* FNA;
  std::string output_file_name;
  std::ofstream fout;

  void put_doa_version();
  void put_start_id();
  void put_acceptance();
  void put_transitions();
 public:
  output_data(const std::string& output_file_name, NFA* FNA) :
      output_file_name(output_file_name), FNA(FNA) {}

  void put();
};
