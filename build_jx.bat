@echo off
title Build jx1-vs2022 (REBUILD)
setlocal

set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
set SLN=%~dp0SwordOnline\Sources\JXAll.sln
set LOGDIR=%~dp0buildlog

if not exist "%LOGDIR%" mkdir "%LOGDIR%"
del /q "%LOGDIR%\*.*" 2>nul

echo ============================================
echo   [1/2] REBUILD cau hinh SERVER: Debug^|Win32
echo ============================================
%MSBUILD% "%SLN%" /t:Rebuild /p:Configuration=Debug /p:Platform=Win32 /m /nologo ^
  /fl1 /flp1:logfile=%LOGDIR%\srv_full.log;verbosity=normal;encoding=UTF-8 ^
  /fl2 /flp2:logfile=%LOGDIR%\srv_errors.log;errorsonly;encoding=UTF-8
echo   -^> exit code: %ERRORLEVEL%

echo.
echo ============================================
echo   [2/2] REBUILD cau hinh CLIENT: Client Debug^|Win32
echo ============================================
%MSBUILD% "%SLN%" /t:Rebuild /p:Configuration="Client Debug" /p:Platform=Win32 /m /nologo ^
  /fl1 /flp1:logfile=%LOGDIR%\cli_full.log;verbosity=normal;encoding=UTF-8 ^
  /fl2 /flp2:logfile=%LOGDIR%\cli_errors.log;errorsonly;encoding=UTF-8
echo   -^> exit code: %ERRORLEVEL%

echo.
echo ============================================
echo   XONG. Log: %LOGDIR%
echo ============================================
timeout /t 8 >nul
