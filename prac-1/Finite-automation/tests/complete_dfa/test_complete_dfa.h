#include "gtest/gtest.h"
#include "../../lib/complete_DFA.h"

#ifndef TEST_COMPLETED_DFA_H
#define TEST_COMPLETED_DFA_H

class complete_DFA_test : public ::testing::Test {
 protected:
  std::vector<DFA*> data;

  virtual void SetUp() {
    data.push_back(new DFA("tests/test_input_1.doa"));
    data.push_back(new DFA("tests/test_input_2.doa"));
    data.push_back(new DFA("tests/test_input_3.doa"));
  }

  virtual void TearDown() {}
};

#endif