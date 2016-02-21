cmake_minimum_required(VERSION 2.8.8)
project(ClangAstExport)

# Include Paths
include_directories($ENV{LLVM_BUILD_ROOT}/include)
include_directories($ENV{LLVM_BUILD_ROOT}/tools/clang/include)
include_directories($ENV{SVN_ROOT}/llvm/include)
include_directories($ENV{SVN_ROOT}/llvm/tools/clang/include)
# include_directories($ENV{CLANG_DIR}/include)

# Link Library Paths
# TODO: How to switch between Release/Debug target?
link_directories($ENV{LLVM_BUILD_ROOT}/Debug/lib)

# Source Files
FILE(GLOB_RECURSE  SOURCE_FILES *.cpp | *.h)
add_executable(ClangAstExport ${SOURCE_FILES})

# Link Libraries
target_link_libraries(ClangAstExport
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
  LLVMSupport
)
