#include "complete_DFA.h"

void complete_DFA::add_dummy_state() {
  uint32_t dummy_state_id = _state_cnt + 1;
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    if (!_gr[state_id].empty()) {
      for (char symbol: alphabet) {
        if (symbol != '#' && _gr[state_id][std::string{symbol}].empty()) {
          _gr[state_id][std::string{symbol}].insert(dummy_state_id);
        }
      }
    }
  }
  ++_state_cnt;
  _gr.emplace_back();
  _is_finish.emplace_back();
  _node_to_set[dummy_state_id] = {dummy_state_id};
  for (char symbol: alphabet) {
    if (symbol != '#') {
      _gr[dummy_state_id][std::string{symbol}].insert(dummy_state_id);
    }
  }
  clear_not_reachable_states();
}