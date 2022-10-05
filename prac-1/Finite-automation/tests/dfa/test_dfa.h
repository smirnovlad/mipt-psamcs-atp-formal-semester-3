#include "gtest/gtest.h"
#include "../../lib/DFA.h"

#ifndef TEST_DFA_H
#define TEST_DFA_H

class DFA_test : public ::testing::Test {
 protected:
  std::vector<one_letter_NFA*> data;

  virtual void SetUp() {
    data.push_back(new one_letter_NFA("tests/test_input_1.doa"));
    data.push_back(new one_letter_NFA("tests/test_input_2.doa"));
    data.push_back(new one_letter_NFA("tests/test_input_3.doa"));
  }

  virtual void TearDown() {}
 public:
  bool is_transition_length_equal_to_one(const DFA& obj);
  bool is_each_reachable(const DFA& obj);
  bool is_each_finishible(const DFA& obj);
  void get_set_of_recognizable(std::set<std::string>& set,
                               const one_letter_NFA& obj,
                               std::string cur_str, uint32_t cur_state_id,
                               uint32_t max_length);
  bool are_the_sets_of_recognizable_the_same(const one_letter_NFA& arg1, const DFA& arg2);
  bool is_determined(const DFA& obj);
};

#endif