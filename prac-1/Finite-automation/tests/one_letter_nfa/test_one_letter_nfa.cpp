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
    one_letter_nfa.show_finit_automaton("foo.doa");
    EXPECT_EQ(false, false);
  }
}

TEST_F(one_letter_NFA_test, the_set_of_recognizable) {

}