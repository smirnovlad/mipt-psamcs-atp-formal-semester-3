#include "test_one_letter_nfa.h"
#include "../../lib/one_letter_NFA.h"

bool one_letter_NFA_test::is_transition_length_equal_to_one(
    const one_letter_NFA& obj) {
  for (uint32_t state_id = 1; state_id <= obj._state_cnt; ++state_id) {
    for (auto& [str, state_set]: obj._gr[state_id]) {
      if (str.size() != 1) {
        return false;
      }
    }
  }
  return true;
}

TEST_F(one_letter_NFA_test, one_letter_transitions) {
  for (auto ptr: data) {
    NFA& nfa = *ptr;
    one_letter_NFA one_letter_nfa(nfa);
    EXPECT_EQ(is_transition_length_equal_to_one(one_letter_nfa), true);
  }
}

bool one_letter_NFA_test::is_each_reachable(const one_letter_NFA& obj) {
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

TEST_F(one_letter_NFA_test, is_each_reachable) {
  for (auto ptr: data) {
    NFA& nfa = *ptr;
    one_letter_NFA one_letter_nfa(nfa);
    EXPECT_EQ(is_each_reachable(one_letter_nfa), true);
  }
}

bool one_letter_NFA_test::is_each_finishible(const one_letter_NFA& obj) {
  // one dfs-call is more efficiently, but currently there is enough dfs functions... :)
  // mb to do
  for (uint32_t state_id = 1; state_id <= obj._state_cnt; ++state_id) {
    bool is_finishible = obj._is_finish[state_id];
    std::vector<bool> used(obj._state_cnt + 1, false);
    std::queue<uint32_t> q;
    q.push(state_id);
    while (!q.empty()) {
      uint32_t front_state = q.front();
      q.pop();
      used[front_state] = true;
      for (auto& [str, state_set]: obj._gr[front_state]) {
        for (uint32_t cur_state_id: state_set) {
          if (!used[cur_state_id]) {
            if (obj._is_finish[cur_state_id]) {
              is_finishible = true;
              break;
            }
            q.push(cur_state_id);
          }
        }
      }
    }
    if (!is_finishible) {
      return false;
    }
  }
  return true;
}

TEST_F(one_letter_NFA_test, is_each_finishible) {
  for (auto ptr: data) {
    NFA& nfa = *ptr;
    one_letter_NFA one_letter_nfa(nfa);
    EXPECT_EQ(is_each_finishible(one_letter_nfa), true);
  }
}

TEST_F(one_letter_NFA_test, cover_show_function) {
  for (auto ptr: data) {
    NFA& nfa = *ptr;
    one_letter_NFA one_letter_nfa(nfa);
    one_letter_nfa.show_finit_automaton("test_one_letter.doa");
    EXPECT_EQ(false, false);
  }
}

void one_letter_NFA_test::get_set_of_recognizable(
    std::set<std::string>& set, const NFA& obj,
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

bool one_letter_NFA_test::are_the_sets_of_recognizable_the_same(
    const NFA& arg1, const one_letter_NFA& arg2) {
  uint32_t max_length = 5;
  std::set<std::string> set1;
  get_set_of_recognizable(set1, arg1, "", arg1._start_id, max_length);
  std::set<std::string> set2;
  get_set_of_recognizable(set2, arg2, "", arg2._start_id, max_length);
  return (set1 == set2);
}

TEST_F(one_letter_NFA_test, the_set_of_recognizable) {
  for (auto ptr: data) {
    NFA& nfa = *ptr;
    one_letter_NFA one_letter_nfa(nfa);
    EXPECT_EQ(true, are_the_sets_of_recognizable_the_same(nfa, one_letter_nfa));
  }
}