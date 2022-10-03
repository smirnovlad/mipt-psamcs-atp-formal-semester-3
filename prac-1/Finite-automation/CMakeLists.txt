cmake_minimum_required(VERSION 2.8)
project(Finite_automation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(MAIN_SOURCE main.cpp)
set(MAIN_SOURCE_LIB src/NFA.cpp
        src/one_letter_NFA.cpp
        src/DFA.cpp
        src/complete_DFA.cpp
        src/minimal_complete_DFA.cpp
        src/input_data.cpp
        src/output_data.cpp)

add_library(foo STATIC ${MAIN_SOURCE_LIB})
add_executable(main ${MAIN_SOURCE})
target_link_libraries(main foo)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCE main_test.cpp)
set(TEST_SOURCE_LIB test/src/test_nfa.cpp
        test/src/test_one_letter_nfa.cpp
        test/src/test_dfa.cpp
        test/src/test_complete_dfa.cpp
        test/src/test_minimal_complete_dfa.cpp)

add_library(test STATIC ${TEST_SOURCE_LIB} ${MAIN_SOURCE_LIB})
add_executable(main_test ${TEST_SOURCE})
target_link_libraries(main_test ${GTEST_LIBRARIES} pthread test)

target_include_directories(main_test PRIVATE ${CMAKE_SOURCE_DIR})