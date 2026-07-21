# Copy test artifacts to build directory
file(COPY "${CMAKE_SOURCE_DIR}/data/test_files" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/data")

include("${CMAKE_SOURCE_DIR}/cmake/google_test.cmake")

# Create binary for test execution
add_executable(
        code_inspector_tests
        main.cpp
        test_bb_info.cpp
        test_func_info.cpp
        test_io.cpp
        test_llvm_utils.cpp
)

# Link gtest as static library
target_link_libraries(
        code_inspector_tests
        gtest_main
        gmock_main
        libcode_inspector
)

# Automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(
        code_inspector_tests
        PROPERTIES LABELS
        "unit"
        DISCOVERY_TIMEOUT # How long to wait (in seconds) before crashing
        240
)
