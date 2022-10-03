#include "DFA.h"

class complete_DFA : public DFA {
 private:
  void add_dummy_state();
 public:
  complete_DFA() = default;

  complete_DFA(const DFA& dfa) : DFA(dfa) {
    add_dummy_state();
  }
};