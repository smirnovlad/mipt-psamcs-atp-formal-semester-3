#include "gtest/gtest.h"
#include "../../lib/one_letter_NFA.h"

class one_letter_NFA_test : public ::testing::Test {
 protected:
  NFA* nfa_1;
  NFA* nfa_2;
  NFA* nfa_3;

  virtual void SetUp() {
    // TODO: solve previous path-problem
    nfa_1 = new NFA("test/test_input_1.doa");
    nfa_2 = new NFA("test/test_input_2.doa");
    nfa_3 = new NFA("test/test_input_3.doa");
  }

  virtual void TearDown() {
    delete nfa_1;
    delete nfa_2;
    delete nfa_3;
  }
};