add_executable(clang_ast_export_exe 
  $ENV{CLANG_AST_EXPORT_EXE_MAIN_DIR}/clang_ast_export_main.cpp)

target_link_libraries(clang_ast_export_exe
  clang_ast_export_lib
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangDriver
  clangEdit
  clangFrontend
  clangLex
  clangParse
  clangRewrite
  clangSema
  clangSerialization
  clangTooling
  clangToolingCore
  LLVMBitReader
  LLVMCore
  LLVMMC
  LLVMMCParser
  LLVMOption
  LLVMProfileData
  LLVMSupport
  version
)

message("Working directory: " ${CMAKE_BINARY_DIR})
find_package(PythonInterp REQUIRED)
add_test(NAME clang_ast_export_exe_test COMMAND ${PYTHON_EXECUTABLE} $ENV{CLANG_AST_EXPORT_TEST_DIR}/clang_ast_export_exe_test.py --clang_ast_export_exe_file=clang_ast_export_exe/${CMAKE_BUILD_TYPE}/clang_ast_export_exe.exe --input_file=$ENV{CLANG_AST_EXPORT_TEST_DIR}/test_decl_input.cc --result_output_file=$ENV{CLANG_AST_EXPORT_TEST_DIR}/test_decl_result.txt --expected_output_file=$ENV{CLANG_AST_EXPORT_TEST_DIR}/test_decl_output.txt WORKING_DIRECTORY ${CMAKE_BINARY_DIR})