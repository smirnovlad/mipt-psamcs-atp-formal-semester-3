#include "../complete_DFA/complete_DFA.h"

class minimal_complete_DFA : public complete_DFA {
 private:
  void get_equivalence_class(std::vector<uint32_t>& equivalence_class,
                             uint32_t& equivalence_class_cnt);
  void get_minimal_complete_DFA();
 public:
  minimal_complete_DFA() = default;

  minimal_complete_DFA(const complete_DFA& complete_dfa) :
      complete_DFA(complete_dfa) {
    get_minimal_complete_DFA();
  }
};