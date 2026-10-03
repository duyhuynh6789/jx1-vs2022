@echo off
setlocal
set "ROOT=%~dp0"
start "" powershell.exe -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File "%ROOT%dev_dashboard.ps1"
timeout /t 2 /nobreak >nul
start "" "http://localhost:18770/"
endlocal
