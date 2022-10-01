#include "one_letter_NFA.h"

void one_letter_NFA::get_one_letter_finite_automaton() {
  clear_not_reachable_states();
  clear_not_finish_ability_states();
  std::vector<bool> used(_state_cnt + 1, false);
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    minimize_transition_length(state_id);
  }
  _state_cnt = _gr.size() - 1;
  remove_epsilon_transition();
  clear_not_reachable_states();
  clear_not_finish_ability_states();
}

void one_letter_NFA::DFS_to_check_reachability(uint32_t state_id,
                                               std::vector<bool>& used,
                                               std::vector<bool>& is_reachable) {
  used[state_id] = true;
  is_reachable[state_id] = true;
  for (const auto& [str, set]: _gr[state_id]) {
    for (uint32_t cur_state_id: set) {
      if (!used[cur_state_id]) {
        DFS_to_check_reachability(cur_state_id, used, is_reachable);
      }
    }
  }
}

bool one_letter_NFA::DFS_to_check_finish_ability(uint32_t state_id,
                                                 std::vector<bool>& used,
                                                 std::vector<bool>& is_finish_ability) {
  used[state_id] = true;
  for (const auto& [str, set]: _gr[state_id]) {
    for (uint32_t cur_state_id: set) {
      if (!used[cur_state_id]) {
        is_finish_ability[state_id] = (is_finish_ability[state_id] ||
                                       DFS_to_check_finish_ability(cur_state_id,
                                                                   used,
                                                                   is_finish_ability));
      }
    }
  }
  return is_finish_ability[state_id];
}

void one_letter_NFA::clear_not_reachable_states() {
  // can we reach that state starting from start-state?
  std::vector<bool> is_reachable(_state_cnt + 1, false);
  std::vector<bool> used(_state_cnt + 1, false);
  DFS_to_check_reachability(_start_id, used, is_reachable);
  update_transitions(is_reachable);
}

void one_letter_NFA::clear_not_finish_ability_states() {
  // can we reach finish-state?
  std::vector<bool> is_finish_ability = _is_finish;
  std::vector<bool> used(_state_cnt + 1, false);
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    used.assign(_state_cnt + 1, false);
    DFS_to_check_finish_ability(state_id, used, is_finish_ability);
  }
  update_transitions(is_finish_ability);
}

void one_letter_NFA::update_transitions(const std::vector<bool>& to_save) {
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    if (!to_save[state_id]) {
      _gr[state_id].clear();
      _is_finish[state_id] = false;
    } else {
      Transitions tmp = _gr[state_id];
      _gr[state_id].clear();
      for (const auto& [str, set]: tmp) {
        for (uint32_t cur_state_id: set) {
          if (to_save[cur_state_id]) {
            _gr[state_id][str].insert(cur_state_id);
          }
        }
      }
    }
  }
}

void one_letter_NFA::minimize_transition_length(uint32_t state_id) {
  Transitions tmp = _gr[state_id];
  for (auto& [str, set]: tmp) {
    for (uint32_t cur_state_id: set) {
      uint32_t length = str.size();
      if (length > 1) {
        while (length > 1) {
          _gr.emplace_back();
          _is_finish.emplace_back();
          _gr.back()[{str[length - 1]}].insert(cur_state_id);
          alphabet.insert(str[length - 1]);
          cur_state_id = _gr.size() - 1;
          --length;
        }
        _gr[state_id][{str[length - 1]}].insert(cur_state_id);
      }
      alphabet.insert(str[0]);
    }
  }
  for (auto [str, set]: tmp) {
    if (str.size() > 1) {
      _gr[state_id][str].clear();
    }
  }
}

bool one_letter_NFA::DFS_to_remove_eps_transition(uint32_t state_id,
                                                  std::vector<bool>& used,
                                                  Transitions& new_states) {
  used[state_id] = true;
  for (const auto& [str, set]: _gr[state_id]) {
    for (uint32_t cur_state_id: set) {
      if (str == "#") {
        if (!used[cur_state_id]) {
          _is_finish[state_id] = (DFS_to_remove_eps_transition(cur_state_id, used, new_states)
                                  || _is_finish[state_id]); // not another order!!!
        }
      } else {
        used[cur_state_id] = true;
        new_states[str].insert(cur_state_id);
      }
    }
  }
  return _is_finish[state_id];
}

void one_letter_NFA::remove_epsilon_transition() {
  std::vector<bool> used(_state_cnt + 1, false);
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    used.assign(_state_cnt + 1, false);
    Transitions new_states;
    DFS_to_remove_eps_transition(state_id, used, new_states);
    _gr[state_id] = new_states;
  }
}