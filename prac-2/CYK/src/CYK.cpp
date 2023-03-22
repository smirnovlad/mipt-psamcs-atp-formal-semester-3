#include "CYK.h"
#include "inputData.h"
#include "outputData.h"

void CYK::getCYK(const std::string &inputFileName) {
  inputData getter(inputFileName, this);
  getter.getCYK();
}

void CYK::recognize(const std::string &toRecognizeFileName, const std::string &outputFileName) {
  outputData outputter(outputFileName, this);
  std::string pathToRecognizeFile = "../" + toRecognizeFileName;
  std::ifstream fin(pathToRecognizeFile);
  std::vector<bool> res;
  while (!fin.eof()) {
    std::string word;
    fin >> word;
    uint32_t n = word.size();
    std::map<std::tuple<char, uint32_t, uint32_t>, bool> dp;
    for (uint32_t len = 1; len <= n; ++len) {
      for (uint32_t i = 0; i + len <= n; ++i) {
        if (len == 1) {
          for (const auto &m : toTerminal) {
            char from = m.first;
            if (toTerminal[from].find(word[i]) != toTerminal[from].end()) {
              dp[std::make_tuple(from, i, i)] = true;
            }
          }
        } else {
          uint32_t j = i + len - 1;
          for (const auto &p : toNonTerminal) {
            char from = p.first;
            for (auto to : toNonTerminal[from]) {
              char left = to.first;
              char right = to.second;
              for (uint32_t k = i; k < j && !dp[std::make_tuple(from, i, j)]; ++k) {
                dp[std::make_tuple(from, i, j)] = dp[std::make_tuple(left, i, k)] &&
                    dp[std::make_tuple(right, k + 1, j)];
                if (dp[std::make_tuple(from, i, j)]) {
                  break;
                }
              }
            }
          }
        }
      }
    }

    res.push_back(dp[std::make_tuple('S', 0, n - 1)]);
  }
  outputter.put(res);
  fin.close();
}