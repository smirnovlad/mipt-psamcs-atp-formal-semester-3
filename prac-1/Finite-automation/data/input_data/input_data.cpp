#include "input_data.h"
#include "../../NFA/NFA.h"

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