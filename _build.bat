@ECHO OFF

VERIFY OTHER 2>nul
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
IF NOT ERRORLEVEL 0 (
  echo Unable to enable extensions
)

FOR /F "delims=" %%A IN ('cd') DO SET "ORIGINAL_DIR=%%A"
ECHO orig dir: %ORIGINAL_DIR%

SET "logFolder=.\_build_logs"

GOTO :main

:doCommand
SET "logFile=%logFolder%\%~1.log"
SET "command=%~2"
ECHO %command%>"%logFile%" 2>&1
%command%>>"%logFile%" 2>&1
EXIT /B %ERRORLEVEL%

:main

cd "%SCRIPT_DIR%"

RMDIR /S /Q "%ORIGINAL_DIR%\%logFolder%"
RMDIR /S /Q "%ORIGINAL_DIR%\_dest"
REM RMDIR /S /Q "%ORIGINAL_DIR%\.xmake"
REM RMDIR /S /Q "%ORIGINAL_DIR%\build"

MKDIR "%ORIGINAL_DIR%\%logFolder%"
MKDIR "%ORIGINAL_DIR%\_dest"

CALL :doCommand "00_made_build_logs" "echo we did it" && cd>NUL || Goto :END

CALL :doCommand "01_xmake_set_theme" "xmake global --theme=plain" && cd>NUL || Goto :END

REM CALL :doCommand "02_xmake_configure_debug" "xmake config -vD --plat=windows --arch=x64 --kind=shared --mode=debug --runtimes=MDd --qt=E:/_D/Qt/5.15.2/msvc2019_64 --yes --policies=package.precompiled:n" && cd>NUL || Goto :END

REM CALL :doCommand "03_xmake_build_debug" "xmake build -a -vD" && cd>NUL || Goto :END

CALL :doCommand "04_xmake_configure_release" "xmake config -vD --plat=windows --arch=x64 --kind=shared --mode=release --runtimes=MD --qt=E:/_D/Qt/5.15.2/msvc2019_64 --yes --policies=package.precompiled:n" && cd>NUL || Goto :END

CALL :doCommand "05_xmake_build_release" "xmake build -a -vD" && cd>NUL || Goto :END

REM CALL :doCommand "50_xmake_test_Audio-Interface-Test" "xmake run -vD Audio-Interface-Test" && cd>NUL || Goto :END
REM CALL :doCommand "50_xmake_test_Configuration-Test" "xmake run -vD Configuration-Test" && cd>NUL || Goto :END
REM CALL :doCommand "50_xmake_test_Logger-Test" "xmake run -vD Logger-Test" && cd>NUL || Goto :END
REM CALL :doCommand "50_xmake_test_Login-Server-Test" "xmake run -vD Login-Server-Test" && cd>NUL || Goto :END
REM CALL :doCommand "50_xmake_test_Network-Messages-Test" "xmake run -vD Network-Messages-Test" && cd>NUL || Goto :END
REM CALL :doCommand "50_xmake_test_Recording-Server-Test" "xmake run -vD Recording-Server-Test" && cd>NUL || Goto :END
REM CALL :doCommand "50_xmake_test_Settings-Interface-Test" "xmake run -vD Settings-Interface-Test" && cd>NUL || Goto :END

ECHO SUCCESS

:END
cd %ORIGINAL_DIR%
ENDLOCAL
EXIT /B %ERRORLEVEL%
