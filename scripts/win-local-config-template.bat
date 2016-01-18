REM Please review and update these settings according to your system configuration.
REM
REM SVN_ROOT: SVN directory to download the LLVM and Clang SVN repositories. See http://llvm.org/docs/GettingStartedVS.html#software
SET SVN_ROOT=%CLANG_AST_EXPORT_GIT_ROOT%\..\svn

REM LLVM_BUILD_ROOT: The directory for LLVM and Clang build files.
SET LLVM_BUILD_ROOT=%CLANG_AST_EXPORT_GIT_ROOT%\..\llvm-build

REM VISUAL_STUIOD_VSDEVCM: Path to batch file to open the Visual Studio command line.
REM ie. C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat
REM SET VISUAL_STUDIO_VSDEVCMD=C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\VsDevCmd.bat

REM CMAKE_INSTALL_PREFIX
