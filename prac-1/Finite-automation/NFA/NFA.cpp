#include "NFA.h"
#include "../data/input_data/input_data.h"
#include "../data/output_data/output_data.h"

void NFA::get_finite_automaton() {
  input_data getter("input.doa", this);
  getter.get();
}

void NFA::show_finit_automaton(const std::string& output_file_name) {
  output_data outputter(output_file_name, this);
  outputter.put();
}