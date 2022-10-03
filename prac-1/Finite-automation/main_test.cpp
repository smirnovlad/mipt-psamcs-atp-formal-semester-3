#include "test/lib/test_nfa.h"
#include "test/lib/test_one_letter_nfa.h"
#include "test/lib/test_dfa.h"
#include "test/lib/test_complete_dfa.h"
#include "test/lib/test_minimal_complete_dfa.h"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}