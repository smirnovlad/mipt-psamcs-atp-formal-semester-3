#include "one_letter_NFA.h"

#ifndef DFA_H_INCLUDED
#define DFA_H_INCLUDED

class DFA : public one_letter_NFA {
 private:
  void get_set_to_node_values();
  void update_gr(std::map<std::set<uint32_t>, bool>& used);
  void get_new_sets(std::map<std::set<uint32_t>, bool>& used);
  void get_deterministic_finite_automaton();
 public:
  DFA() = default;

  DFA(const std::string& input_file_name) :
      one_letter_NFA(input_file_name) {
    get_deterministic_finite_automaton();
  }

  DFA(const one_letter_NFA& one_letter_nfa) :
      one_letter_NFA(one_letter_nfa) {
    get_deterministic_finite_automaton();
  }
};

#endif