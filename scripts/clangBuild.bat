@echo off
REM Compiler
set CXX=clang-cl

REM Compiler flags
set CXXFLAGS=/Ihdr /Isrc /Imysql-connector-c++-9.4.0-winx64/include /std:c++17 /EHsc

REM get scripts folder by checking pwd essentially for bat file and remove the ending \
set SCRIPT_DIR=%~dp0
set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

REM Relative LIBPATH -needed for when it calls the runtime dll in \bin
set LINK_FLAGS=/link /LIBPATH:"%SCRIPT_DIR%\..\mysql-connector-c++-9.4.0-winx64\lib64\vs14"

REM Library to link
set LINK_LIBS=mysqlcppconn.lib

REM Source files
set SRC=%SCRIPT_DIR%\..\src\*.cpp

REM Output executable in PAXEL\bin
set OUT=%SCRIPT_DIR%\..\bin\ClangProgram.exe

REM Ensure bin exists
if not exist "%SCRIPT_DIR%\..\bin" mkdir "%SCRIPT_DIR%\..\bin"

echo Attempting Build...

REM Build command (quote the variable here)
%CXX% %CXXFLAGS% %SRC% %LINK_FLAGS% %LINK_LIBS% /OUT:"%OUT%"



if %ERRORLEVEL% EQU 0 (
    echo Build complete: %OUT%
) else (
    echo Build Failed
)
pause
