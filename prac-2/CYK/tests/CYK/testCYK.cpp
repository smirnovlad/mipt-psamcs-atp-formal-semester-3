#include "testCYK.h"
#include "CYK.h"

bool CYKTest::simpleTest(CYK &obj,
                         const std::string &toRecognizeFileName,
                         const std::string &trueAnsFileName) {
  obj.recognize(toRecognizeFileName, "output.txt");
  std::ifstream fin1, fin2;
  fin1.open("output.txt");
  fin2.open(trueAnsFileName);
  while (!fin1.eof()) {
    std::string res1, res2;
    fin1 >> res1;
    fin2 >> res2;
    if (res1 != res2) {
      std::cout << "res1 = " << res1 << ", res2 = " << res2 << '\n';
      return false;
    }
  }
  return true;
}

TEST_F(CYKTest, simpleTest) {
  for (uint32_t i = 0; i < arr.size(); ++i) {
    CYK &cyk = *arr[i];
    std::string toRecognizeFileName = toRecognize[i];
    std::string trueAnsFileName = ans[i];
    EXPECT_EQ(simpleTest(cyk, toRecognizeFileName, trueAnsFileName), true);
  }
}
