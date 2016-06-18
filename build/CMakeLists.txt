cmake_minimum_required(VERSION 2.8.8)
project(clang_ast_export)

set (ENABLE_TESTING 1)
include(CTest)
set(CTEST_PROJECT_NAME "MyProject")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=MyProject")
set(CTEST_DROP_SITE_CDASH TRUE)

include_directories($ENV{LLVM_BUILD_ROOT}/include)
include_directories($ENV{LLVM_BUILD_ROOT}/tools/clang/include)
include_directories($ENV{SVN_ROOT}/llvm/include)
include_directories($ENV{SVN_ROOT}/llvm/tools/clang/include)
include_directories($ENV{CLANG_AST_EXPORT_SOURCE_DIR})

link_directories($ENV{LLVM_BUILD_ROOT}/\$\(Configuration\)/lib)

add_subdirectory(clang_ast_export_lib)
add_subdirectory(clang_ast_export_exe)

# find_package(PkgConfig)
# pkg_check_modules(GTEST REQUIRED gtest>=1.7.0)
# pkg_check_modules(GMOCK REQUIRED gmock>=1.7.0)

# include_directories(
  # ${GTEST_INCLUDE_DIRS}
  # ${GMOCK_INCLUDE_DIRS}
# )

# # We need thread support
# find_package(Threads REQUIRED)

# # Enable ExternalProject CMake module
# include(ExternalProject)

# # Download and install GoogleTest
# ExternalProject_Add(
    # gtest
    # URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
    # PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # # Disable install step
    # INSTALL_COMMAND ""
# )

# # Create a libgtest target to be used as a dependency by test programs
# add_library(libgtest IMPORTED STATIC GLOBAL)
# add_dependencies(libgtest gtest)

# # Set gtest properties
# ExternalProject_Get_Property(gtest source_dir binary_dir)
# set_target_properties(libgtest PROPERTIES
    # "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
    # "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
# #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
# )
# # I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
# include_directories("${source_dir}/include")

# # Download and install GoogleMock
# ExternalProject_Add(
    # gmock
    # URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
    # PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
    # # Disable install step
    # INSTALL_COMMAND ""
# )

# # Create a libgmock target to be used as a dependency by test programs
# add_library(libgmock IMPORTED STATIC GLOBAL)
# add_dependencies(libgmock gmock)

# # Set gmock properties
# ExternalProject_Get_Property(gmock source_dir binary_dir)
# set_target_properties(libgmock PROPERTIES
    # "IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
    # "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
# #    "INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
# )
# # I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
# include_directories("${source_dir}/include")