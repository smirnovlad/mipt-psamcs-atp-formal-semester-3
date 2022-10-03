#include "gtest/gtest.h"
#include "../../lib/DFA.h"

class DFA_test : public ::testing::Test {
 protected:
  one_letter_NFA* one_letter_nfa_1;
  one_letter_NFA* one_letter_nfa_2;
  one_letter_NFA* one_letter_nfa_3;

  virtual void SetUp() {
    one_letter_nfa_1 = new one_letter_NFA("test/test_input_1.doa");
    one_letter_nfa_2 = new one_letter_NFA("test/test_input_2.doa");
    one_letter_nfa_3 = new one_letter_NFA("test/test_input_3.doa");
  }

  virtual void TearDown() {
    delete one_letter_nfa_1;
    delete one_letter_nfa_2;
    delete one_letter_nfa_3;
  }
};