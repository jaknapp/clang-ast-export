@ECHO OFF

REM Flag to indicate the script should end early.
SET NEEDS_SCRIPT_END=

ECHO Setting up for clang-ast-export. Press Ctrl+c to exit at any time.
ECHO Press any key to continue.
SET /P INPUT=Type input: %=%

SET GIT_PATH=
FOR /f "delims=" %%A IN ('where git') DO SET "GIT_PATH=%%A"
ECHO "%GIT_PATH%"
IF "%GIT_PATH%"=="" (
  ECHO "Please install git. Then press any key to continue.
  SET /P INPUT=Type input: %=%
  )

IF NOT EXIST .git (
  ECHO Enter a path to use for the clang-ast-export git repository or press enter to use the current working directory.
  SET CLANG_AST_EXPORT_GIT_ROOT=
  SET /P CLANG_AST_EXPORT_GIT_ROOT=Type input: %=%
  )

IF "%CLANG_AST_EXPORT_GIT_ROOT"=="" (
  SET CLANG_AST_EXPORT_GIT_ROOT=%cd%
  ECHO Using %CLANG_AST_EXPORT_GIT_ROOT%.
  )

IF NOT EXIST .git (
  CD %CLANG_AST_EXPORT_GIT_ROOT%
  git init
  git remote add origin %GIT_URL%
  git pull origin master
  )

SET CLANG_AST_EXPORT_GIT_LOCAL_ROOT=%CLANG_AST_EXPORT_GIT_ROOT%\local
SET CLANG_AST_EXPORT_GIT_LOCAL_CONFIG=%CLANG_AST_EXPORT_GIT_ROOT%\win-config.bat
IF NOT EXIST %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG% (
  ECHO Setting up a local submodule to store your configuration file(s) at %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%.
  MD %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%
  CD %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%
  git init
  COPY %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%\scripts\win-local-config-template.bat %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG%
  git commit -am "Created local config file from template."
  CD %CLANG_AST_EXPORT_GIT_ROOT%
  git submodule add %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%
  ECHO Please edit the configuration of %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG% if needed.
  ECHO Press any key to continue.
  SET /P INPUT=Type input: %=%
  )

CALL local\win-config.bat

IF "%SVN_ROOT%"=="" (
  ECHO Please set SVN_ROOT in %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG%.
  SET NEEDS_SCRIPT_END=1
  )

IF "%LLVM_BUILD_ROOT%"=="" (
  ECHO Please set LLVM_BUILD_ROOT in %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG%.
  SET NEEDS_SCRIPT_END=1
  )

IF "%LLVM_LIT_TOOLS_DIR%"=="" (
  ECHO Please set LLVM_LIT_TOOLS_DIR in %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG%.
  SET NEEDS_SCRIPT_END=1
  )
  
IF NOT "%NEEDS_SCRIPT_END%"=="" (
  GOTO :SCRIPT_END
  )

ECHO Checking for required tools for LLVM\Clang. See http://clang.llvm.org/get_started.html. 
ECHO   1. Subversion
ECHO   2. CMake
ECHO   3. Visual Studio (2013 or later) - Not checked
ECHO   4. Python
ECHO   5. GnuWin32 - Not checked

FOR /f "delims=" %%A IN ('where svn') DO SET "SVN_PATH=%%A"
IF "%SVN_PATH%"=="" (
  ECHO Please install svn. http://subversion.apache.org/packages.html#windows
  ECHO Press any key to continue.
  SET /P INPUT=Type input: %=%
  )

FOR /f "delims=" %%A IN ('where cmake') DO SET "CMAKE_PATH=%%A"
IF "%CMAKE_PATH%"=="" (
  ECHO Please install cmake. http://www.cmake.org/cmake/resources/software.html
  ECHO See http://llvm.org/docs/CMake.html
  ECHO See http://llvm.org/docs/CMake.html#quick-start
  ECHO Press any key to continue.
  SET /P INPUT=Type input: %=%
  )

FOR /f "delims=" %%A IN ('where python') DO SET "PYTHON_PATH=%%A"
IF "%PYTHON_PATH%"=="" (
  ECHO Please install python. https://www.python.org/downloads/windows/
  ECHO Press any key to continue.
  SET /P INPUT=Type input: %=%
  )

ECHO Downloading LLVM and Clang. See http://llvm.org/docs/GettingStartedVS.html#getting-started

MD %SVN_ROOT%
CD %SVN_ROOT%
svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm
CD llvm\tools
svn co http://llvm.org/svn/llvm-project/cfe/trunk clang

ECHO Building LLVM/Clang.

SET LLVM_SRC_ROOT=%SVN_ROOT%\llvm
CD %LLVM_SRC_ROOT%
MD %LLVM_BUILD_ROOT%
cmake -DLLVM_LIT_TOOLS_DIR=%GNUWIN32_PATH% -G "Visual Studio 12" %LLVM_BUILD_ROOT%
REM "E:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat" && MSBuild /m:8 /p:Configuration=Release E:\dev\svn\build-custom\tools\clang\tools\driver\clang.vcxproj
REM "E:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat" && MSBuild /m:8 /p:Configuration=Release E:\dev\svn\build-custom\LLVM.sln
REM "E:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat" && MSBuild /m:8 /p:Configuration=Release E:\dev\svn\build-custom\check-all.vcxproj

CD %LLVM_BUILD_ROOT%
cmake --build .
python ..\build\bin\llvm-lit --param build_config=Win32 --param build_mode=Release --param llvm_site_config=../build/test/lit.site.cfg test

:SCRIPT_END
