#include "gtest/gtest.h"
#include "one_letter_NFA.h"

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
  void get_set_of_recognizable(std::set<std::string>& set,
                               const NFA& obj,
                               std::string cur_str, uint32_t cur_state_id,
                               uint32_t max_length);
  bool are_the_sets_of_recognizable_the_same(const NFA& arg1, const one_letter_NFA& arg2);
};

#endif