#include "gtest/gtest.h"
#include "../../lib/complete_DFA.h"

class complete_DFA_test : public ::testing::Test {
 protected:
  DFA* dfa_1;
  DFA* dfa_2;
  DFA* dfa_3;

  virtual void SetUp() {
    dfa_1 = new DFA("test/test_input_1.doa");
    dfa_2 = new DFA("test/test_input_2.doa");
    dfa_3 = new DFA("test/test_input_3.doa");
  }

  virtual void TearDown() {
    delete dfa_1;
    delete dfa_2;
    delete dfa_3;
  }
};