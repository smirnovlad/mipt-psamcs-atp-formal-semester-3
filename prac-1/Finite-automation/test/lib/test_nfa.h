#include "gtest/gtest.h"
#include "../../lib/NFA.h"

class NFA_test : public ::testing::Test {
 protected:
  NFA* nfa_1;
  NFA* nfa_2;
  NFA* nfa_3;

  virtual void SetUp() {
    nfa_1 = new NFA("test_input_1.doa");
    nfa_2 = new NFA("test_input_2.doa");
    nfa_3 = new NFA("test_input_3.doa");
  }

  virtual void TearDown() {
    delete nfa_1;
    delete nfa_2;
    delete nfa_3;
  }
};