set(TARGET_NAME "one_letter_nfa")
set(COVERAGE_NAME "one_letter_nfa_coverage")
set(COVERAGE_TARGET "one_letter_nfa_coverage_target")
set(SOURCE_DIR_MAIN "${myApp_SOURCE_DIR}")
set(SOURCES ${myApp_source_files})

message(INFO ${SOURCES})

set(TEST_SOURCES
        ../one_letter_nfa/test_one_letter_nfa.h
        ../one_letter_nfa/test_one_letter_nfa.cpp
        )
run_coverage(
        "${TEST_SOURCES}"
        "${SOURCES}"
        "${COVERAGE_TARGET}"
        "${TARGET_NAME}"
        "${COVERAGE_NAME}"
)
