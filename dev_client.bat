@echo off
setlocal
title JX2022 - Fast Client Build & Run

set "ROOT=%~dp0"
set "MSBUILD=C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
set "CLIENT_PROJ=%ROOT%SwordOnline\Sources\S3Client\S3Client.vcxproj"
set "CLIENT_EXE=%ROOT%bin\client\Game.exe"

echo ============================================
echo   JX2022 FAST CLIENT BUILD + RUN
echo   Server will NOT be restarted.
echo ============================================
echo.

if not exist "%MSBUILD%" (
    echo [ERROR] MSBuild not found:
    echo %MSBUILD%
    pause
    exit /b 1
)

if not exist "%CLIENT_PROJ%" (
    echo [ERROR] Client project not found:
    echo %CLIENT_PROJ%
    pause
    exit /b 1
)

echo [1/3] Stop CLIENT only (if running)...
taskkill /IM Game.exe /T /F >nul 2>&1

echo [2/3] Incremental build: S3Client / Debug / Win32...
"%MSBUILD%" "%CLIENT_PROJ%" /t:Build /p:Configuration=Debug /p:Platform=Win32 /m /nologo
if errorlevel 1 (
    echo.
    echo [ERROR] Client build failed. Server was not touched.
    pause
    exit /b 1
)

if not exist "%CLIENT_EXE%" (
    echo.
    echo [ERROR] Build succeeded but Game.exe was not found:
    echo %CLIENT_EXE%
    pause
    exit /b 1
)

echo.
echo [3/3] Start CLIENT...
start "JX2022 Client" /D "%ROOT%bin\client" "%CLIENT_EXE%"

echo.
echo ============================================
echo   READY - SERVER WAS LEFT RUNNING
echo ============================================
endlocal
