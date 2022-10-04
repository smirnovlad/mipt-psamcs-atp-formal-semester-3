cmake_minimum_required(VERSION 2.8)
project(Finite_automation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/main_test.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")

set(MAIN_SOURCE main.cpp)
set(MAIN_SOURCE_LIB src/NFA.cpp
        src/one_letter_NFA.cpp
        src/DFA.cpp
        src/complete_DFA.cpp
        src/minimal_complete_DFA.cpp
        src/input_data.cpp
        src/output_data.cpp)

add_library(MAIN_LIB STATIC ${MAIN_SOURCE_LIB})
add_executable(main ${MAIN_SOURCE})
target_link_libraries(main MAIN_LIB)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#set(OBJECT_TEST_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/main_test.dir)
#message("-- Object testing files will be output to: ${OBJECT_TEST_DIR}")

set(TEST_SOURCE main_test.cpp)
set(TEST_SOURCE_LIB test/src/test_nfa.cpp
        test/src/test_one_letter_nfa.cpp
        test/src/test_dfa.cpp
        test/src/test_complete_dfa.cpp
        test/src/test_minimal_complete_dfa.cpp)

add_library(TEST_LIB STATIC ${TEST_SOURCE_LIB} ${MAIN_SOURCE_LIB})
add_executable(main_test ${TEST_SOURCE})
target_link_libraries(main_test ${GTEST_LIBRARIES} pthread TEST_LIB)

target_include_directories(main_test PRIVATE ${CMAKE_SOURCE_DIR})

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
        COMMAND mkdir -p coverage
        COMMAND ${CMAKE_MAKE_PROGRAM} test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
add_custom_command(TARGET gcov
        COMMAND echo "=================== GCOV ===================="
        COMMAND gcov -b ${CMAKE_SOURCE_DIR}/main_test.cpp -o ${OBJECT_DIR}
        | grep -A 5 "main_test.cpp" > CoverageSummary.tmp
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/bin/coverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage  # Need separate command for this line
        )
add_dependencies(gcov main_test)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated
# .gcda and .gcno files.
add_custom_target(scrub
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        COMMAND rm -f ${OBJECT_DIR}/main_test.gcno
        COMMAND rm -f ${OBJECT_DIR}/main_test.gcda
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

# Testing
enable_testing()
add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/main_test)