#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <queue>


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