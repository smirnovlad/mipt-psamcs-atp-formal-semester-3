#include "../lib/minimal_complete_DFA.h"

void minimal_complete_DFA::get_equivalence_class(
    std::vector<uint32_t>& equivalence_class,
    uint32_t& equivalence_class_cnt) {
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    equivalence_class[state_id] = !_is_finish[state_id] + 1;
  }
  std::vector<uint32_t> tmp;
  while (tmp != equivalence_class) {
    tmp = equivalence_class;
    std::map<std::vector<uint32_t>, uint32_t> classes;
    for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
      std::vector<uint32_t> state_subsequence(alphabet.size(), 0);
      state_subsequence[0] = tmp[state_id];
      uint32_t symbol_id = 1;
      for (char symbol: alphabet) {
        if (symbol != '#') {
          uint32_t to = *(_gr[state_id][std::string{symbol}].begin());
          state_subsequence[symbol_id] = tmp[to];
          ++symbol_id;
        }
      }
      auto it = classes.find(state_subsequence);
      if (it != classes.end()) {
        equivalence_class[state_id] = it->second;
      } else {
        equivalence_class[state_id] = classes.size() + 1;
        classes[state_subsequence] = equivalence_class[state_id];
      }
    }
  }
  for (uint32_t val: equivalence_class) {
    equivalence_class_cnt = std::max(equivalence_class_cnt, val);
  }
}

void minimal_complete_DFA::get_minimal_complete_DFA() {
  std::vector<uint32_t> equivalence_class(_state_cnt + 1, 0);
  uint32_t equivalence_class_cnt = 0;
  get_equivalence_class(equivalence_class, equivalence_class_cnt);
  std::vector<Transitions> new_gr(equivalence_class_cnt + 1);
  std::vector<bool> new_is_finish(equivalence_class_cnt + 1);
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    for (char symbol: alphabet) {
      if (symbol != '#') {
        uint32_t to = *(_gr[state_id][std::string{symbol}].begin());
        new_gr[equivalence_class[state_id]][std::string{symbol}].insert(
            equivalence_class[to]);
        if (_is_finish[state_id]) {
          new_is_finish[equivalence_class[state_id]] = true;
        }
      }
    }
  }
  _gr = new_gr;
  _is_finish = new_is_finish;
  _state_cnt = equivalence_class_cnt;
  _start_id = equivalence_class[_start_id];
  clear_not_reachable_states();
}