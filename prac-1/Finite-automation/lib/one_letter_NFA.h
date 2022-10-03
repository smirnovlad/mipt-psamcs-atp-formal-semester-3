#include "NFA.h"

#ifndef ONE_LETTER_NFA_H_INCLUDED
#define ONE_LETTER_NFA_H_INCLUDED

class one_letter_NFA : public NFA {
 private:
  void DFS_to_check_reachability(uint32_t state_id, std::vector<bool>& used,
                                 std::vector<bool>& is_reachable);
  bool DFS_to_check_finish_ability(uint32_t state_id, std::vector<bool>& used,
                                   std::vector<bool>& is_finish_ability);
  void update_transitions(const std::vector<bool>& to_save);
  void minimize_transition_length(uint32_t state_id);
  void remove_epsilon_transition();
  void get_one_letter_finite_automaton();
  bool DFS_to_remove_eps_transition(uint32_t state_id, std::vector<bool>& used,
                                    Transitions& new_states);
 protected:
  void clear_not_reachable_states();
  void clear_not_finish_ability_states();
 public:
  one_letter_NFA() = default;

  one_letter_NFA(const std::string& input_file_name) : NFA(input_file_name) {
    get_one_letter_finite_automaton();
  }

  one_letter_NFA(const NFA& nfa) : NFA(nfa) {
    get_one_letter_finite_automaton();
  }
};

#endif