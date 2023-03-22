set(TARGET_NAME "CYK")
set(COVERAGE_NAME "CYKCoverage")
set(COVERAGE_TARGET "CYKCoverageTarget")
set(SOURCE_DIR_MAIN "${myApp_SOURCE_DIR}")
#set(SOURCES ${myApp_source_files})
set(SOURCES "${PROJECT_SOURCE_DIR}/src/CYK.cpp"
        "${PROJECT_SOURCE_DIR}/src/inputData.cpp"
        "${PROJECT_SOURCE_DIR}/src/outputData.cpp")

message(INFO ${SOURCES})

set(TEST_SOURCES
        testCYK.h
        testCYK.cpp
        )
run_coverage(
        "${TEST_SOURCES}"
        "${SOURCES}"
        "${COVERAGE_TARGET}"
        "${TARGET_NAME}"
        "${COVERAGE_NAME}"
)
