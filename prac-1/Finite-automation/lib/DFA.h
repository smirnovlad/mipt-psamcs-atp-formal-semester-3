#include "one_letter_NFA.h"

class DFA : public one_letter_NFA {
 private:
  void get_set_to_node_values();
  void update_gr(std::map<std::set<uint32_t>, bool>& used);
  void get_new_sets(std::map<std::set<uint32_t>, bool>& used);
  void get_deterministic_finite_automaton();
 public:
  DFA() = default;

  DFA(const one_letter_NFA& one_letter_nfa) :
      one_letter_NFA(one_letter_nfa) {
    get_deterministic_finite_automaton();
  }
};