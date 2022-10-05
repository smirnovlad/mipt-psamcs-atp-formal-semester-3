#include "../../cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h"
#include "../../lib/one_letter_NFA.h"

#ifndef TEST_ONE_LETTER_NFA_H
#define TEST_ONE_LETTER_NFA_H

class one_letter_NFA_test : public ::testing::Test {
 protected:
  std::vector<NFA*> data;

  virtual void SetUp() {
    // TODO: solve previous path-problem
    data.push_back(new NFA("tests/test_input_1.doa"));
    data.push_back(new NFA("tests/test_input_2.doa"));
    data.push_back(new NFA("tests/test_input_3.doa"));
  }

  virtual void TearDown() {}
 public:
  bool is_transition_length_equal_to_one(const one_letter_NFA& obj);
  bool is_each_reachable(const one_letter_NFA& obj);
  bool is_each_finishible(const one_letter_NFA& obj);
};

#endif