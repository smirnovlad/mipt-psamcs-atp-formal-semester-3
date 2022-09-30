#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class input_data;

class output_data;

class finite_automaton {
 protected:
  struct Transition {
    uint32_t _to = 0;
    std::string _str = std::string();
  };
  uint32_t _state_cnt = 0;
  uint32_t _start_id = 0;
  std::vector<std::vector<Transition>> _gr;
  std::vector<bool> _is_finish;
  void get_finite_automaton();

  friend class input_data;

  friend class output_data;

 public:
  finite_automaton() {
    get_finite_automaton();
  }

  finite_automaton(const finite_automaton& other) = default;

  void show_finit_automaton();
};

class output_data {
 private:
  finite_automaton* FNA;
  std::string output_file_name;
  std::ofstream fout;

  void put_doa_version();
  void put_start_id();
  void put_acceptance();
  void put_transitions();
 public:
  output_data(const std::string& output_file_name, finite_automaton* FNA) :
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
      for (const auto& [to, str]: FNA->_gr[state_id]) {
        fout << "  -> " << str << ' ' << to << '\n';
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
  finite_automaton* FNA;
  std::string input_file_name;
  std::ifstream fin;

  std::string get_doa_version();
  uint32_t get_start_id();
  void get_acceptance();
  void get_transitions();
  void update_state_cnt(uint32_t state_id);
 public:
  input_data(const std::string& input_file_name, finite_automaton* FNA) :
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
        finite_automaton::Transition edge;
        iss >> edge._str;
        iss >> edge._to;
        update_state_cnt(edge._to);
        FNA->_gr[current_state_id].push_back(edge);
      }
    }
  }
}

void input_data::get() {
  // TODO: read state_cnt
  fin.open(input_file_name);
  std::string DOA = get_doa_version();
  FNA->_start_id = get_start_id();
  get_acceptance();
  get_transitions();
  fin.close();
}

void finite_automaton::get_finite_automaton() {
  input_data getter("input.doa", this);
  getter.get();
}

void finite_automaton::show_finit_automaton() {
  output_data outputter("output.doa", this);
  outputter.put();
}

class one_letter_finite_automaton : public finite_automaton {
 private:
  void DFS_to_check_reachability(uint32_t state_id, std::vector<bool>& used,
                                 std::vector<bool>& is_reachable);
  bool DFS_to_check_finish_ability(uint32_t state_id, std::vector<bool>& used,
                                   std::vector<bool>& is_finish_ability);
  void clear_useless_states();
  void update_transitions(const std::vector<bool>& to_save);
  void minimize_transition_length(uint32_t state_id);
  void remove_epsilon_transition();
  void get_one_letter_finite_automaton();
  bool DFS_to_remove_eps_transition(uint32_t state_id, std::vector<bool>& used,
                                    std::vector<Transition>& new_states);
 public:
  one_letter_finite_automaton(const finite_automaton& NFA) : finite_automaton(NFA) {
    get_one_letter_finite_automaton();
  }
};

void one_letter_finite_automaton::get_one_letter_finite_automaton() {
  clear_useless_states();
  std::vector<bool> used(_state_cnt + 1, false);
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    minimize_transition_length(state_id);
  }
  _state_cnt = _gr.size() - 1;
  remove_epsilon_transition();
  clear_useless_states();
}

void one_letter_finite_automaton::DFS_to_check_reachability(uint32_t state_id,
                                                            std::vector<bool>& used,
                                                            std::vector<bool>& is_reachable) {
  used[state_id] = true;
  is_reachable[state_id] = true;
  for (const auto& [to, str]: _gr[state_id]) {
    if (!used[to]) {
      DFS_to_check_reachability(to, used, is_reachable);
    }
  }
}

bool one_letter_finite_automaton::DFS_to_check_finish_ability(uint32_t state_id,
                                                              std::vector<bool>& used,
                                                              std::vector<bool>& is_finish_ability) {
  used[state_id] = true;
  for (const auto& edge: _gr[state_id]) {
    if (!used[edge._to]) {
      is_finish_ability[state_id] = (is_finish_ability[state_id] ||
                                     DFS_to_check_finish_ability(edge._to, used, is_finish_ability));
    }
  }
  return is_finish_ability[state_id];
}

void one_letter_finite_automaton::clear_useless_states() {
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

void one_letter_finite_automaton::update_transitions(const std::vector<bool>& to_save) {
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    if (!to_save[state_id]) {
      _gr[state_id].clear();
      _is_finish[state_id] = false;
    } else {
      std::vector<Transition> tmp = _gr[state_id];
      _gr[state_id].clear();
      for (const auto& edge: tmp) {
        if (to_save[edge._to]) {
          _gr[state_id].push_back(edge);
        }
      }
    }
  }
}

void one_letter_finite_automaton::minimize_transition_length(uint32_t state_id) {
  for (auto& [to, str]: _gr[state_id]) {
    uint32_t length = str.size();
    uint32_t cur_state_id = to;
    if (length > 1) {
      while (length > 1) {
        _gr.emplace_back();
        _is_finish.emplace_back();
        Transition edge{cur_state_id, std::string()};
        edge._str = str[length - 1];
        _gr.back().push_back(edge);
        cur_state_id = _gr.size() - 1;
        --length;
      }
    }
    to = cur_state_id;
    str = str[length - 1];
  }
}

bool one_letter_finite_automaton::DFS_to_remove_eps_transition(uint32_t state_id,
                                                               std::vector<bool>& used,
                                                               std::vector<Transition>& new_states) {
  used[state_id] = true;
  for (const auto& edge: _gr[state_id]) {
    if (edge._str == "#") {
      _is_finish[state_id] = (_is_finish[state_id] ||
                              DFS_to_remove_eps_transition(edge._to, used, new_states));
    } else {
      used[edge._to] = true;
      new_states.push_back(edge);
    }
  }
  return _is_finish[state_id];
}

void one_letter_finite_automaton::remove_epsilon_transition() {
  std::vector<bool> used(_state_cnt + 1, false);
  for (uint32_t state_id = 1; state_id <= _state_cnt; ++state_id) {
    used.assign(_state_cnt + 1, false);
    std::vector<Transition> new_states;
    DFS_to_remove_eps_transition(state_id, used, new_states);
    _gr[state_id] = new_states;
  }
}

class deterministic_finite_automaton : protected one_letter_finite_automaton {
 private:
  void get_deterministic_finite_automaton();
 public:
  deterministic_finite_automaton(const one_letter_finite_automaton& one_letter_NFA) :
      one_letter_finite_automaton(one_letter_NFA) {
    get_deterministic_finite_automaton();
  }
};

void deterministic_finite_automaton::get_deterministic_finite_automaton() {

}

int main() {
  finite_automaton NFA;
  //NFA.show_finit_automaton();
  one_letter_finite_automaton one_letter_NFA(NFA);
  one_letter_NFA.show_finit_automaton();
  //deterministic_finite_automaton DKA(one_letter_NFA);


  return 0;
}
