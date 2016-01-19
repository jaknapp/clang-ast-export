REM Please review and update these settings according to your system configuration.

REM SVN_ROOT: Directory to download the LLVM and Clang SVN repositories.
REM See http://llvm.org/docs/GettingStartedVS.html#software
SET SVN_ROOT=%CLANG_AST_EXPORT_GIT_ROOT%\..\svn

REM LLVM_BUILD_ROOT: Directory to store generated LLVM and Clang build files.
SET LLVM_BUILD_ROOT=%CLANG_AST_EXPORT_GIT_ROOT%\..\llvm-build

REM LLVM_LIT_TOOLS_DIR: The directory of the gnuwin32 binaries.
REM   1. Download http://sourceforge.net/projects/getgnuwin32/files/latest/download?source=files
REM   2. Run download.bat
REM   3. Run install.bat
REM   4. Copy gnuwin32 if desired.
REM   5. Enter the path of gnuwin32\bin.
SET LLVM_LIT_TOOLS_DIR=
