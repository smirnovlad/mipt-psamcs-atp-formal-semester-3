#include "gtest/gtest.h"
#include "../../lib/minimal_complete_DFA.h"

class minimal_complete_DFA_test : public ::testing::Test {
 protected:
  std::vector<complete_DFA*> data;

  virtual void SetUp() {
    data.push_back(new complete_DFA("test/test_input_1.doa"));
    data.push_back(new complete_DFA("test/test_input_2.doa"));
    data.push_back(new complete_DFA("test/test_input_3.doa"));
  }

  virtual void TearDown() {}
};