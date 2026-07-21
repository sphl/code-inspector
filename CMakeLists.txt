cmake_minimum_required(VERSION 3.16)

project(
    code-inspector
    VERSION 0.1
    DESCRIPTION "An LLVM-based code property inspector."
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(CODE_COVERAGE "Enable code coverage instrumentation" OFF)

# --- LLVM ---
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# --- SVF ---
if (NOT SVF_DIR)
    if (DEFINED ENV{SVF_DIR})
        set(SVF_DIR "$ENV{SVF_DIR}" CACHE PATH "Root directory of the SVF installation")
    else ()
        message(FATAL_ERROR
            "SVF_DIR is not set.  Please either:\n"
            "  - pass -DSVF_DIR=<path> to CMake, or\n"
            "  - set the SVF_DIR environment variable\n"
            "pointing to the SVF source/build root (e.g. /opt/svf-2.2).")
    endif ()
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(_svf_build_dir "${SVF_DIR}/Debug-build")
else ()
    set(_svf_build_dir "${SVF_DIR}/Release-build")
endif ()

set(SVF_INCLUDE_DIRS
    "${SVF_DIR}/include"
    "${_svf_build_dir}/include"
)

find_library(SVF_LIB
    NAMES Svf
    PATHS "${_svf_build_dir}/lib"
    NO_DEFAULT_PATH
    DOC "SVF library (libSvf)"
)

if (NOT SVF_LIB)
    message(FATAL_ERROR
        "Could not find libSvf under ${_svf_build_dir}/lib.\n"
        "Make sure SVF has been built (./build.sh) before configuring this project.")
endif ()

message(STATUS "Found SVF: ${SVF_LIB}")

# --- Code coverage ---
if (CODE_COVERAGE AND UNIX)
    add_compile_options(--coverage)
    add_link_options(--coverage)
    message(STATUS "Code coverage enabled")
endif ()

set(CODE_INSPECTOR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
