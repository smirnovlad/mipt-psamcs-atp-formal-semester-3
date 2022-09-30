#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <queue>

class input_data;

class output_data;

class NFA {
 protected:
  using Transitions = std::map<std::string, std::set<uint32_t>>;

  uint32_t _state_cnt = 0;
  uint32_t _start_id = 0;
  std::set<char> alphabet;
  std::vector<Transitions> _gr;
  std::vector<bool> _is_finish;

  std::map<std::set<uint32_t>, uint32_t> _set_to_node;
  std::map<uint32_t, std::set<uint32_t>> _node_to_set;

  void get_finite_automaton();

  friend class input_data;

  friend class output_data;

 public:
  NFA() {
    alphabet.insert('#');
    get_finite_automaton();
  }

  NFA(const NFA& other) = default;

  void show_finit_automaton(const std::string& output_file_name);
};

class output_data {
 private:
  NFA* FNA;
  std::string output_file_name;
  std::ofstream fout;

  void put_doa_version();
  void put_start_id();
  void put_acceptance();
  void put_transitions();
 public:
  output_data(const std::string& output_file_name, NFA* FNA) :
      output_file_name(output_file_name), FNA(FNA) {}

  void put();
};

void output_data::put_doa_version() {
  fout << "DOA: v1\n";
}

void output_data::put_start_id() {
  fout << "Start: " << FNA->_start_id << '\n';
}

void output_data::put_acceptance() {
  fout << "Acceptance: ";
  bool is_one = false;
  for (uint32_t state_id = 1; state_id <= FNA->_state_cnt; ++state_id) {
    if (FNA->_is_finish[state_id]) {
      if (is_one) {
        fout << " & ";
      } else {
        is_one = true;
      }
      fout << state_id;
    }
  }
}

void output_data::put_transitions() {
  fout << "\n--BEGIN--\n";
  for (uint32_t state_id = 1; state_id <= FNA->_state_cnt; ++state_id) {
    if (!FNA->_gr[state_id].empty() || FNA->_is_finish[state_id]) {
      fout << "State: " << state_id << '\n';
      for (const auto& [str, set]: FNA->_gr[state_id]) {
        for (uint32_t cur_state_id: set) {
          fout << "    -> " << str << ' ' << cur_state_id << '\n';
        }
      }
    }
  }
  fout << "--END--\n";
}

void output_data::put() {
  fout.open(output_file_name);
  put_doa_version();
  put_start_id();
  put_acceptance();
  put_transitions();
  fout.close();
}

class input_data {
 private:
  NFA* FNA;
  std::string input_file_name;
  std::ifstream fin;

  std::string get_doa_version();
  uint32_t get_start_id();
  void get_acceptance();
  void get_transitions();
  void update_state_cnt(uint32_t state_id);
 public:
  input_data(const std::string& input_file_name, NFA* FNA) :
      input_file_name(input_file_name), FNA(FNA) {}

  void get();
};

std::string input_data::get_doa_version() {
  std::string line;
  std::getline(fin, line);
  std::istringstream iss(line);
  std::string tmp, doa_version;
  iss >> tmp >> doa_version;
  return doa_version;
}

void input_data::update_state_cnt(uint32_t state_id) {
  if (state_id > FNA->_state_cnt) {
    FNA->_state_cnt = state_id;
    FNA->_gr.resize(FNA->_state_cnt + 1);
    FNA->_is_finish.resize(FNA->_state_cnt + 1);
  }
}

uint32_t input_data::get_start_id() {
  std::string line;
  std::getline(fin, line);
  std::istringstream iss(line);
  std::string tmp;
  uint32_t start_id;
  iss >> tmp >> start_id;
  update_state_cnt(start_id);
  return start_id;
}

void input_data::get_acceptance() {
  std::string line;
  std::getline(fin, line);
  std::istringstream iss(line);
  std::string tmp;
  uint32_t state_id;
  while (iss >> tmp) {
    iss >> state_id;
    update_state_cnt(state_id);
    FNA->_is_finish[state_id] = true;
  }
}

void input_data::get_transitions() {
  uint32_t current_state_id = 0;
  while (!fin.eof()) {
    std::string line;
    std::getline(fin, line);
    if (line != "--BEGIN--" && line != "--END--") {
      std::istringstream iss(line);
      std::string tmp;
      iss >> tmp;
      if (tmp == "State:") {
        iss >> current_state_id;
        update_state_cnt(current_state_id);
      } else {
        std::string str;
        uint32_t to;
        iss >> str;
        iss >> to;
        update_state_cnt(to);
        FNA->_gr[current_state_id][str].insert(to);
      }
    }
  }
}

void input_data::get() {
  fin.open(input_file_name);
  std::string DOA = get_doa_version();
  FNA->_start_id = get_start_id();
  get_acceptance();
  get_transitions();
  fin.close();
}

void NFA::get_finite_automaton() {
  input_data getter("input.doa", this);
  getter.get();
}

void NFA::show_finit_automaton(const std::string& output_file_name) {
  output_data outputter(output_file_name, this);
  outputter.put();
}

class one_letter_NFA : public NFA {
 private:
  void DFS_to_check_reachability(uint32_t state_id, std::vector<bool>& used,
                                 std::vector<bool>& is_reachable);
  bool DFS_to_check_finish_ability(uint32_t state_id, std::vector<bool>& used,
                                   std::vector<bool>& is_finish_ability);
  void update_transitions(const std::vector<bool>& to_save);
  void minimize_transition_length(uint32_t state_id);
  void remove_epsilon_transition();
  void get_one_letter_finite_automaton();
  bool DFS_to_remove_eps_transition(uint32_t state_id, std::vector<bool>& used,
                                    Transitions& new_states);
 protected:
  void clear_useless_states();
 public:
  one_letter_NFA() = default;

  one_letter_NFA(const NFA& nfa) : NFA(nfa) {
    get_one_letter_finite_automaton();
  }
};

void one_letter_NFA::get_one_letter_finite_automaton() {
  // clear_useless_states();
  std::vector<bool> used(_state_cnt + 1, false);
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    minimize_transition_length(state_id);
  }
  _state_cnt = _gr.size() - 1;
  remove_epsilon_transition();
  // clear_useless_states();
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

void one_letter_NFA::clear_useless_states() {
  // can we reach finish-state and can we reach that state starting from start-state?
  std::vector<bool> is_reachable(_state_cnt + 1, false);
  std::vector<bool> used(_state_cnt + 1, false);
  DFS_to_check_reachability(_start_id, used, is_reachable);


  std::vector<bool> is_finish_ability = _is_finish;
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    if (is_reachable[state_id]) {
      used.assign(_state_cnt + 1, false);
      DFS_to_check_finish_ability(state_id, used, is_finish_ability);
    } else {
      is_finish_ability[state_id] = false;
    }
  }

  std::vector<bool> to_save = is_finish_ability;
  update_transitions(to_save);
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

class DFA : public one_letter_NFA {
 private:
  void get_set_to_node_values();
  void update_gr(std::map<std::set<uint32_t>, bool>& used);
  void get_new_sets(std::map<std::set<uint32_t>, bool>& used);
  void get_deterministic_finite_automaton();
 public:
  DFA() = default;

  DFA(const one_letter_NFA& one_letter_nfa) :
      one_letter_NFA(one_letter_nfa) {
    get_deterministic_finite_automaton();
  }
};

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
    /* std::cout << "-----------\ncurrent node: " << _set_to_node[state_set] << '\n';
    for (auto el: state_set) {
      std::cout << el << ' ';
    }
    std::cout << '\n'; */
    uint32_t state_id = _set_to_node[state_set];
    for (char symbol: alphabet) {
      if (symbol != '#') {
        // std::cout << symbol << '\n';
        std::set<uint32_t> set;
        for (uint32_t cur_state_id: state_set) {
          std::set<uint32_t> to_merge = _gr[cur_state_id][std::string{symbol}];
          set.insert(to_merge.begin(), to_merge.end());
        }
        /* std::cout << "set: ";
        for (auto el: set) {
          std::cout << el << ' ';
        }
        std::cout << '\n'; */
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
}

class minimal_complete_DFA : public complete_DFA {
 private:
  void get_equivalence_class(std::vector<uint32_t>& equivalence_class,
                             uint32_t& equivalence_class_cnt);
  void get_minimal_complete_DFA();
 public:
  minimal_complete_DFA() = default;

  minimal_complete_DFA(const complete_DFA& complete_dfa) :
      complete_DFA(complete_dfa) {
    get_minimal_complete_DFA();
  }
};

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
}

int main() {
  NFA NFA;
  NFA.show_finit_automaton("nfa.doa");

  one_letter_NFA one_letter_NFA(NFA);
  one_letter_NFA.show_finit_automaton("one_letter_nfa.doa");

  DFA DFA(one_letter_NFA);
  DFA.show_finit_automaton("dfa.doa");

  complete_DFA complete_DFA(DFA);
  complete_DFA.show_finit_automaton("complete_dfa.doa");

  minimal_complete_DFA minimal_complete_DFA(complete_DFA);
  minimal_complete_DFA.show_finit_automaton("output.doa");

  return 0;
}
