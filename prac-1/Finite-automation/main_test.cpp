#include "test/src/test_one_letter_nfa.cpp"
#include "test/src/test_dfa.cpp"
#include "test/src/test_complete_dfa.cpp"
#include "test/src/test_minimal_complete_dfa.cpp"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}