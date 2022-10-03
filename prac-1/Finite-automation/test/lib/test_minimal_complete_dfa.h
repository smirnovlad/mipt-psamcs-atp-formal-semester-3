#include "gtest/gtest.h"
#include "../../lib/minimal_complete_DFA.h"

class minimal_complete_DFA_test : public ::testing::Test {
 protected:
  complete_DFA* complete_dfa_1;
  complete_DFA* complete_dfa_2;
  complete_DFA* complete_dfa_3;

  virtual void SetUp() {
    complete_dfa_1 = new complete_DFA("test/test_input_1.doa");
    complete_dfa_2 = new complete_DFA("test/test_input_2.doa");
    complete_dfa_3 = new complete_DFA("test/test_input_3.doa");
  }

  virtual void TearDown() {
    delete complete_dfa_1;
    delete complete_dfa_2;
    delete complete_dfa_3;
  }
};