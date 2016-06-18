FILE(GLOB_RECURSE SOURCE_FILES
  $ENV{CLANG_AST_EXPORT_SOURCE_DIR}/*.cpp |
  $ENV{CLANG_AST_EXPORT_SOURCE_DIR}/*.h
)
add_library(clang_ast_export_lib STATIC ${SOURCE_FILES})

# cmake_minimum_required(VERSION 2.6)
# project(basic_test)

# ################################
# # GTest
# ################################
# ADD_SUBDIRECTORY (gtest-1.6.0)
# enable_testing()
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# ################################
# # Unit Tests
# ################################
# # Add test cpp file
# add_executable( runUnitTests testgtest.cpp )
# # Link test executable against gtest & gtest_main
# target_link_libraries(runUnitTests gtest gtest_main)
# add_test( runUnitTests runUnitTests )