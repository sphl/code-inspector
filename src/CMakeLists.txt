llvm_map_components_to_libnames(
    LLVM_LIBS
    analysis
    bitwriter
    core
    irreader
    support
    transformutils
)

add_library(
    libcode_inspector STATIC
    container/bb_info.cpp
    container/func_info.cpp
    utils/io.cpp
    utils/llvm_utils.cpp
    utils/pretty_printer.cpp
    inspection.cpp
)

target_include_directories(libcode_inspector PUBLIC ${SVF_INCLUDE_DIRS} ${CODE_INSPECTOR_INCLUDE_DIR} ${LLVM_INCLUDE_DIRS})
target_compile_definitions(libcode_inspector PUBLIC ${LLVM_DEFINITIONS})
target_link_libraries(libcode_inspector PRIVATE ${LLVM_LIBS} ${SVF_LIB})
set_target_properties(libcode_inspector PROPERTIES PREFIX "")

add_executable(code_inspector main.cpp)

target_compile_options(code_inspector PRIVATE -fno-rtti)
target_link_libraries(code_inspector PRIVATE libcode_inspector ${SVF_LIB})
set_target_properties(code_inspector PROPERTIES
    OUTPUT_NAME "code-inspector"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
