#include "NFA.h"
#include "input_data.h"
#include "output_data.h"

void NFA::get_finite_automaton(const std::string& input_file_name) {
  input_data getter(input_file_name, this);
  getter.get();
}

void NFA::show_finit_automaton(const std::string& output_file_name) {
  output_data outputter(output_file_name, this);
  outputter.put();
}