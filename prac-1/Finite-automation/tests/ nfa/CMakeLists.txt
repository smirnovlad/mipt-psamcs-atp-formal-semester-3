set(TARGET_NAME "nfa")
set(COVERAGE_NAME "nfa_coverage")
set(COVERAGE_TARGET "nfa_coverage_target")
set(SOURCE_DIR_MAIN "${myApp_SOURCE_DIR}")
set(SOURCES ${myApp_source_files})

message(INFO ${SOURCES})

set(TEST_SOURCES
        ../nfa/test_nfa.h
        ../nfa/test_nfa.cpp
        )
run_coverage(
        "${TEST_SOURCES}"
        "${SOURCES}"
        "${COVERAGE_TARGET}"
        "${TARGET_NAME}"
        "${COVERAGE_NAME}"
)
