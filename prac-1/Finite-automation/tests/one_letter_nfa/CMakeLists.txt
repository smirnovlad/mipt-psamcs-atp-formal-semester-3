set(TARGET_NAME "one_letter_nfa")
set(COVERAGE_NAME "one_letter_nfa_coverage")
set(COVERAGE_TARGET "one_letter_nfa_coverage_target")
#set(SOURCES ${myApp_source_files})
set(SOURCES "${PROJECT_SOURCE_DIR}/src/NFA.cpp"
        "${PROJECT_SOURCE_DIR}/src/one_letter_NFA.cpp"
        "${PROJECT_SOURCE_DIR}/src/input_data.cpp"
        "${PROJECT_SOURCE_DIR}/src/output_data.cpp"
        )

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
