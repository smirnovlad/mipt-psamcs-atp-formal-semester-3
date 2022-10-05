#include "../lib/DFA.h"

void DFA::get_set_to_node_values() {
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    _set_to_node[{state_id}] = state_id;
    _node_to_set[state_id] = {state_id};
  }
}

void DFA::update_gr(std::map<std::set<uint32_t>, bool>& used) {
  std::vector<Transitions> new_gr(_gr.size());
  std::vector<bool> new_is_finish(_gr.size(), false);
  for (auto& [set, b]: used) {
    uint32_t state_id = _set_to_node[set];
    new_gr[state_id] = _gr[state_id];
    new_is_finish[state_id] = _is_finish[state_id];
  }
  _gr = new_gr;
  _is_finish = new_is_finish;
}

void DFA::get_new_sets(std::map<std::set<uint32_t>, bool>& used) {
  std::queue<std::set<uint32_t>> q;
  q.push({_start_id});
  uint32_t cnt = 10;
  while (!q.empty()) {
    std::set<uint32_t> state_set = q.front();
    used[state_set] = true;
    uint32_t state_id = _set_to_node[state_set];
    for (char symbol: alphabet) {
      if (symbol != '#') {
        std::set<uint32_t> set;
        for (uint32_t cur_state_id: state_set) {
          std::set<uint32_t> to_merge = _gr[cur_state_id][std::string{symbol}];
          set.insert(to_merge.begin(), to_merge.end());
        }
        std::set<uint32_t> tmp = set;
        set.clear();
        for (uint32_t cur_state_id: tmp) {
          std::set<uint32_t> cur_set = _node_to_set[cur_state_id];
          set.insert(cur_set.begin(), cur_set.end());
        }
        if (!set.empty() && used.find(set) == used.end()) {
          if (set.size() > 1) {
            _set_to_node[set] = _gr.size();
            _node_to_set[_set_to_node[set]] = set;
            ++_state_cnt;
            _gr.emplace_back();
            _is_finish.emplace_back();
          }
          //std::cout << "new_state_id = " << _set_to_node[set] << '\n';
          for (uint32_t cur_state_id: set) {
            if (_is_finish[cur_state_id]) {
              _is_finish[_set_to_node[set]] = true;
              break;
            }
          }
          q.push(set);
        }
        _gr[state_id][std::string{symbol}].clear();
        if (!set.empty()) {
          _gr[state_id][std::string{symbol}].insert(_set_to_node[set]);
        }
      }
    }
    q.pop();
  }
}

void DFA::get_deterministic_finite_automaton() {
  get_set_to_node_values();
  std::map<std::set<uint32_t>, bool> used;
  get_new_sets(used);
  update_gr(used);
  clear_not_finish_ability_states();
  clear_not_reachable_states();
}

class complete_DFA : public DFA {
 private:
  void add_dummy_state();
 public:
  complete_DFA() = default;

  complete_DFA(const DFA& dfa) : DFA(dfa) {
    add_dummy_state();
  }
};