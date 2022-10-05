set(TARGET_NAME "complete_dfa")
set(COVERAGE_NAME "complete_dfa_coverage")
set(COVERAGE_TARGET "complete_dfa_coverage_target")
set(SOURCE_DIR_MAIN "${myApp_SOURCE_DIR}")
set(SOURCES ${myApp_source_files})

message(INFO ${SOURCES})

set(TEST_SOURCES
        ../complete_dfa/test_complete_dfa.h
        ../complete_dfa/test_complete_dfa.cpp
        )
run_coverage(
        "${TEST_SOURCES}"
        "${SOURCES}"
        "${COVERAGE_TARGET}"
        "${TARGET_NAME}"
        "${COVERAGE_NAME}"
)
