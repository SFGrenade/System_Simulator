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

RMDIR /S /Q %logFolder%

MKDIR %logFolder%

CALL :doCommand "00_made_build_logs" "echo we did it" && cd>NUL || Goto :END

CALL :doCommand "01_xmake_set_theme" "xmake global --theme=plain" && cd>NUL || Goto :END

CALL :doCommand "02_xmake_configure" "xmake config --import=.vscode\xmakeConfig.release.conf -vD -y" && cd>NUL || Goto :END

CALL :doCommand "03_xmake_build" "xmake build -a -vD" && cd>NUL || Goto :END

CALL :doCommand "05_xmake_test_Audio-Interface-Test" "xmake run -vD Audio-Interface-Test" && cd>NUL || Goto :END
CALL :doCommand "05_xmake_test_Configuration-Test" "xmake run -vD Configuration-Test" && cd>NUL || Goto :END
CALL :doCommand "05_xmake_test_Logger-Test" "xmake run -vD Logger-Test" && cd>NUL || Goto :END
CALL :doCommand "05_xmake_test_Login-Server-Test" "xmake run -vD Login-Server-Test" && cd>NUL || Goto :END
CALL :doCommand "05_xmake_test_Network-Messages-Test" "xmake run -vD Network-Messages-Test" && cd>NUL || Goto :END
CALL :doCommand "05_xmake_test_Recording-Server-Test" "xmake run -vD Recording-Server-Test" && cd>NUL || Goto :END
CALL :doCommand "05_xmake_test_Settings-Interface-Test" "xmake run -vD Settings-Interface-Test" && cd>NUL || Goto :END

:END
cd %ORIGINAL_DIR%
ENDLOCAL
EXIT /B %ERRORLEVEL%
