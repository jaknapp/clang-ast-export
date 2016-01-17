@ECHO OFF
SET GIT_PATH=
FOR /f "delims=" %%A IN ('where git') DO SET "GIT_PATH=%%A"
ECHO "%GIT_PATH%"
IF "%GIT_PATH%"=="" (
  ECHO "Please install git."
  GOTO :end
  )
git init
git remote add origin %GIT_URL%
git pull origin master

:end