#include "outputData.h"
#include "CYK.h"

void outputData::put(const std::vector<bool>& res) {
  fout.open(output_file_name);
  for (auto el: res) {
    fout << (el ? "YES" : "NO") << '\n';
  }
  fout.close();
}