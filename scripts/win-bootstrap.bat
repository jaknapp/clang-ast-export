@ECHO OFF

ECHO Setting up for clang-ast-export. Press Ctrl+c to exit at any time.
ECHO Press any key to continue.
SET /P INPUT=Type input: %=%

REM
ECHO Checking for dependencies.
SET GIT_PATH=
FOR /f "delims=" %%A IN ('where git') DO SET "GIT_PATH=%%A"
ECHO "%GIT_PATH%"
IF "%GIT_PATH%"=="" (
  ECHO "Please install git."
  ECHO Press any key to continue.
  SET /P INPUT=Type input: %=%
  )

ECHO Checking for tools required for LLVM\Clang. See http://clang.llvm.org/get_started.html. 
ECHO   1. Subversion
ECHO   2. CMake
ECHO   3. Visual Studio (2013 or later)
ECHO   4. Python
ECHO   5. GnuWin32

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

ECHO Install Visual Studio 2013 or later if needed.
ECHO Press any key to continue.
SET /P INPUT=Type input: %=%

FOR /f "delims=" %%A IN ('where python') DO SET "PYTHON_PATH=%%A"
IF "%PYTHON_PATH%"=="" (
  ECHO Please install python. https://www.python.org/downloads/windows/
  ECHO Press any key to continue.
  SET /P INPUT=Type input: %=%
  )

ECHO Please install GnuWin32 tools.
ECHO   1. Download http://sourceforge.net/projects/getgnuwin32/files/latest/download?source=files
ECHO   2. Run download.bat
ECHO   3. Run install.bat
ECHO   4. Copy gnuwin32 if desired.
REM ECHO   5. Append path to gnuwin32\bin to PATH environment variable.
ECHO   5. Enter the path of gnuwin32\bin.
VAR GNUWIN32_PATH=
SET /P GNUWIN32_PATH=Type input: %=%

ECHO Enter a path to use for the clang-ast-export git repository.
SET CLANG_AST_EXPORT_GIT_ROOT=
SET /P CLANG_AST_EXPORT_GIT_ROOT=Type input: %=%

REM
echo Setting up clang-ast-export git repo."

CD %CLANG_AST_EXPORT_GIT_ROOT%
git init
git remote add origin %GIT_URL%
git pull origin master

ECHO Setting up a local submodule to store your configuration file(s).
SET CLANG_AST_EXPORT_GIT_LOCAL_ROOT=%CLANG_AST_EXPORT_GIT_ROOT%\local
SET CLANG_AST_EXPORT_GIT_LOCAL_CONFIG=%CLANG_AST_EXPORT_GIT_ROOT%\win-config.bat
IF NOT EXIST %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG% (
  MD %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%
  CD %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%
  git init
  COPY %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%\scripts\win-local-config-template.bat %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG%
  git commit -am "Created local config file from template."
  CD %CLANG_AST_EXPORT_GIT_ROOT%
  git submodule add %CLANG_AST_EXPORT_GIT_LOCAL_ROOT%
  )

ECHO Please edit the configuration of %CLANG_AST_EXPORT_GIT_LOCAL_CONFIG% if needed.
ECHO Press any key to continue.
SET /P INPUT=Type input: %=%

:GIT_SETUP_END

REM Download LLVM and Clang.
REM
ECHO Downloading LLVM and Clang. See http://llvm.org/docs/GettingStartedVS.html#getting-started

IF "%SVN_ROOT%"=="" (
  ECHO Please set SVN_ROOT to a directory to install LLVM and Clang.
  GOTO :SCRIPT_END
  )

MD %SVN_ROOT%
CD %SVN_ROOT%
svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm
CD llvm\tools
svn co http://llvm.org/svn/llvm-project/cfe/trunk clang

REM Building LLVM/Clang.
REM
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
