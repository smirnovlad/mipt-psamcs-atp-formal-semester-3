set(TARGET_NAME "dfa")
set(COVERAGE_NAME "dfa_coverage")
set(COVERAGE_TARGET "dfa_coverage_target")
set(SOURCE_DIR_MAIN "${myApp_SOURCE_DIR}")
set(SOURCES ${myApp_source_files})

message(INFO ${SOURCES})

set(TEST_SOURCES
        ../dfa/test_dfa.h
        ../dfa/test_dfa.cpp
        )
run_coverage(
        "${TEST_SOURCES}"
        "${SOURCES}"
        "${COVERAGE_TARGET}"
        "${TARGET_NAME}"
        "${COVERAGE_NAME}"
)
