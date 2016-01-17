# Getting Started
## Windows
set GIT_URL=https://github.com/jaknapp/clang-ast-export.git & bitsadmin.exe /transfer "ClangAstExportWinBootstrap" https://raw.githubusercontent.com/jaknapp/clang-ast-export/master/scripts/win-bootstrap.bat %TEMP%\win-bootstrap.bat & %TEMP%\win-bootstrap.bat
## Mac
GIT_URL=https://github.com/jaknapp/clang-ast-export.git; source < (curl -s echo https://raw.githubusercontent.com/jaknapp/clang-ast-export/master/scripts/mac-bootstrap.sh)
