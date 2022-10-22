#include "gtest/gtest.h"
#include "complete_DFA.h"

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

 public:
  bool is_transition_length_equal_to_one(const complete_DFA& obj);
  bool is_each_reachable(const complete_DFA& obj);
  void get_set_of_recognizable(std::set<std::string>& set,
                               const DFA& obj,
                               std::string cur_str, uint32_t cur_state_id,
                               uint32_t max_length);
  bool are_the_sets_of_recognizable_the_same(const DFA& arg1, const complete_DFA& arg2);
  bool is_complete_determined(const complete_DFA& obj);
};

#endif