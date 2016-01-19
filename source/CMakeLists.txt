# cmake_minimum_required(VERSION 2.8.8)
# project(ClangAstExport)

# find_package(LLVM REQUIRED CONFIG)

# find_package(Clang REQUIRED)
# find_package(Clang REQUIRED clangTooling libClang)

# message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
# message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# # Set your project compile flags.
# # E.g. if using the C++ header files
# # you will need to enable C++11 support
# # for your compiler.

# include_directories(${LLVM_INCLUDE_DIRS})
# add_definitions(${LLVM_DEFINITIONS})

# include_directories(${CLANG_INCLUDE_DIRS})
# add_definitions(${Clang_DEFINITIONS})

# link_directories(${LLVM_BUILD_ROOT}/Release/lib)

# # Now build our tools
# add_executable(clang-ast-export main.cpp)

# # Find the libraries that correspond to the LLVM components
# # that we wish to use
# llvm_map_components_to_libnames(llvm_libs 
  # support
  # core
  # irreader)

# # Link against LLVM libraries
# target_link_libraries(clang-ast-export${llvm_libs}
  # clangTooling
  # clangBasic
  # clangASTMatchers)
  
  
  
  
cmake_minimum_required(VERSION 2.8.8)
project(ClangAstExport)

link_directories($ENV{LLVM_BUILD_ROOT}/Debug/lib)
include_directories(${Clang_DIR}/include)
include_directories(${LLVM_ROOT}/include)

message(STATUS "Link directories: $ENV{LLVM_BUILD_ROOT}/Debug/lib")

set(SOURCE_FILES main.cpp)
add_executable(ClangAstExport ${SOURCE_FILES})

target_link_libraries(ClangAstExport
  clangTooling
  clangBasic
  clangASTMatchers
  # clangFrontend
  # clangSerialization
  # clangDriver
  # clangParse
  # clangSema
  # clangAnalysis
  # clangAST
  # clangBasic
  # clangEdit
  # clangLex
  # clangTooling
)
# llvm_map_components_to_libnames(llvm_libs 
  # support
  # core
  # irreader)

target_link_libraries(ClangAstExport ${llvm_libs}
  # LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
  # LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
  # LLVMX86AsmPrinter # MC, Support, X86Utils
  # LLVMX86Info # MC, Support, Target
  # LLVMX86Utils # Core, Support
  # LLVMipo
  # LLVMScalarOpts
  # LLVMInstCombine
  # LLVMTransformUtils
  # LLVMipa
  # LLVMAnalysis
  # LLVMTarget
  # LLVMOption # Support
  # LLVMMCParser # MC, Support
  # LLVMMC # Object, Support
  # LLVMObject # BitReader, Core, Support
  # LLVMBitReader # Core, Support
  # LLVMCore # Support
  # LLVMSupport
)
