#include "tests/nfa/test_nfa.h"
#include "tests/one_letter_nfa/test_one_letter_nfa.h"
#include "tests/dfa/test_dfa.h"
#include "tests/complete_dfa/test_complete_dfa.h"
#include "tests/minimal_complete_dfa/test_minimal_complete_dfa.h"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}