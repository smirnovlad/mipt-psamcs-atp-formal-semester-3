#include "test_minimal_complete_dfa.h"
#include "../../lib/minimal_complete_DFA.h"

bool minimal_complete_DFA_test::is_transition_length_equal_to_one(
    const minimal_complete_DFA& obj) {
  for (uint32_t state_id = 1; state_id <= obj._state_cnt; ++state_id) {
    for (auto& [str, state_set]: obj._gr[state_id]) {
      if (str.size() != 1) {
        return false;
      }
    }
  }
  return true;
}

TEST_F(minimal_complete_DFA_test, one_letter_transitions) {
  for (auto ptr: data) {
    complete_DFA& complete_dfa = *ptr;
    minimal_complete_DFA minimal_complete_dfa(complete_dfa);
    EXPECT_EQ(is_transition_length_equal_to_one(minimal_complete_dfa), true);
  }
}

bool minimal_complete_DFA_test::is_each_reachable(
    const minimal_complete_DFA& obj) {
  std::vector<bool> used(obj._state_cnt + 1, false);
  std::queue<uint32_t> q;
  q.push(obj._start_id);
  while (!q.empty()) {
    uint32_t state_id = q.front();
    q.pop();
    used[state_id] = true;
    for (auto& [str, state_set]: obj._gr[state_id]) {
      for (uint32_t cur_state_id: state_set) {
        if (!used[cur_state_id]) {
          q.push(cur_state_id);
        }
      }
    }
  }
  for (uint32_t state_id = 1; state_id <= obj._state_cnt; ++state_id) {
    if (!obj._gr[state_id].empty() && !used[state_id]) {
      return false;
    }
  }
  return true;
}

TEST_F(minimal_complete_DFA_test, is_each_reachable) {
  for (auto ptr: data) {
    complete_DFA& complete_dfa = *ptr;
    minimal_complete_DFA minimal_complete_dfa(complete_dfa);
    EXPECT_EQ(is_each_reachable(minimal_complete_dfa), true);
  }
}

bool minimal_complete_DFA_test::is_complete_determined(
    const minimal_complete_DFA& obj) {
  for (uint32_t state_id = 1; state_id <= obj._state_cnt; ++state_id) {
    for (auto& [str, state_set]: obj._gr[state_id]) {
      if (state_set.size() != 1) {
        return false;
      }
    }
  }
  return true;
}

TEST_F(minimal_complete_DFA_test, is_complete_determined) {
  for (auto ptr: data) {
    complete_DFA& complete_dfa = *ptr;
    minimal_complete_DFA minimal_complete_dfa(complete_dfa);
    EXPECT_EQ(is_complete_determined(minimal_complete_dfa), true);
  }
}

TEST_F(minimal_complete_DFA_test, cover_show_function) {
  for (auto ptr: data) {
    complete_DFA& complete_dfa = *ptr;
    minimal_complete_DFA minimal_complete_dfa(complete_dfa);
    minimal_complete_dfa.show_finit_automaton("test_minimal_complete_dfa.doa");
    EXPECT_EQ(false, false);
  }
}

void minimal_complete_DFA_test::get_set_of_recognizable(
    std::set<std::string>& set, const complete_DFA& obj,
    std::string cur_str, uint32_t cur_state_id,
    uint32_t max_length) {
  if (cur_str.size() <= max_length) {
    if (obj._is_finish[cur_state_id]) {
      set.insert(cur_str);
    }
    for (auto& [str, state_set]: obj._gr[cur_state_id]) {
      for (uint32_t state_id: state_set) {
        if (str != "#") {
          get_set_of_recognizable(set, obj, cur_str + str, state_id, max_length);
        } else {
          get_set_of_recognizable(set, obj, cur_str, state_id, max_length);
        }
      }
    }
  }
}

bool minimal_complete_DFA_test::are_the_sets_of_recognizable_the_same(
    const complete_DFA& arg1, const minimal_complete_DFA& arg2) {
  uint32_t max_length = 5;
  std::set<std::string> set1;
  get_set_of_recognizable(set1, arg1, "", arg1._start_id, max_length);
  std::set<std::string> set2;
  get_set_of_recognizable(set2, arg2, "", arg2._start_id, max_length);
  return (set1 == set2);
}

TEST_F(minimal_complete_DFA_test, the_set_of_recognizable) {
  for (auto ptr: data) {
    complete_DFA& complete_dfa = *ptr;
    minimal_complete_DFA minimal_complete_dfa(complete_dfa);
    EXPECT_EQ(are_the_sets_of_recognizable_the_same(complete_dfa,
                                              minimal_complete_dfa), true);
  }
}

//TEST_F(minimal_complete_DFA_test, check_isomorphism) {
//
//}