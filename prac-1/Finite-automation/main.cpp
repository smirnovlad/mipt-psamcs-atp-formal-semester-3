#include "lib/minimal_complete_DFA.h"

int main() {
  NFA NFA("input.doa");
  NFA.show_finit_automaton("nfa.doa");

  one_letter_NFA one_letter_NFA(NFA);
  one_letter_NFA.show_finit_automaton("one_letter_nfa.doa");

  DFA DFA(one_letter_NFA);
  DFA.show_finit_automaton("dfa.doa");

  complete_DFA complete_DFA(DFA);
  complete_DFA.show_finit_automaton("complete_dfa.doa");

  minimal_complete_DFA minimal_complete_DFA(complete_DFA);
  minimal_complete_DFA.show_finit_automaton("output.doa");

  return 0;
}
