#include "gtest/gtest.h"
#include "CYK.h"

#ifndef TEST_CYK_H
#define TEST_CYK_H

class CYKTest : public ::testing::Test {
 protected:
  std::vector<CYK *> arr;
  std::vector<std::string> toRecognize;
  std::vector<std::string> ans;

  virtual void SetUp() {
    arr.push_back(new CYK("tests/CYK/testInput.txt"));
    toRecognize.push_back("tests/CYK/toRecognize.txt");
    ans.push_back("../tests/CYK/trueAns.txt");
  }

  virtual void TearDown() {}

 public:
  bool simpleTest(CYK &obj,
                  const std::string &toRecognizeFileName,
                  const std::string &trueAnsFileName);
};

#endif