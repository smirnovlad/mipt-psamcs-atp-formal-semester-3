#include "output_data.h"
#include "NFA.h"

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