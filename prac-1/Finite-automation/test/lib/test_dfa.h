#include "gtest/gtest.h"
#include "../../lib/DFA.h"

#ifndef TEST_DFA_H
#define TEST_DFA_H

class DFA_test : public ::testing::Test {
 protected:
  std::vector<one_letter_NFA*> data;

  virtual void SetUp() {
    data.push_back(new one_letter_NFA("test/test_input_1.doa"));
    data.push_back(new one_letter_NFA("test/test_input_2.doa"));
    data.push_back(new one_letter_NFA("test/test_input_3.doa"));
  }

  virtual void TearDown() {}
};

#endif