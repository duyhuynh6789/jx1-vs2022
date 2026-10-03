@echo off
setlocal EnableExtensions EnableDelayedExpansion
title JX2022 DEV Incremental Launcher

set "ROOT=%~dp0"
set "SRC=%ROOT%SwordOnline\Sources"
set "MSBUILD=C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
set "RUNTIME=D:\games\bin\bin"
set "SERVER=%RUNTIME%\Server"
set "CLIENT=%RUNTIME%\client"
set "LOG=%ROOT%buildlog"
set "DEVLOG=%ROOT%devlogs"
set "STATE=%TEMP%\jx_dev_projects.txt"

if not exist "%LOG%" mkdir "%LOG%"
if not exist "%DEVLOG%" mkdir "%DEVLOG%"

rem Start the single browser-based monitor. Service windows stay hidden.
powershell -NoProfile -ExecutionPolicy Bypass -Command "if(-not (Get-NetTCPConnection -LocalPort 8765 -State Listen -ErrorAction SilentlyContinue)){Start-Process powershell -WindowStyle Hidden -ArgumentList '-NoProfile','-ExecutionPolicy','Bypass','-File','%ROOT%dev_dashboard.ps1'; Start-Sleep -Milliseconds 500}; Start-Process 'http://localhost:8765/'"

echo ============================================================
echo   JX2022 DEV - TARGETED INCREMENTAL BUILD
echo   Runtime: D:\Games\bin\bin
echo ============================================================
echo.

rem Project mapping. Only the process whose project changed is restarted.
set "P_GameServer=%SRC%\MultiServer\GameServer\GameServer.vcxproj"
set "P_Bishop=%SRC%\MultiServer\Bishop\Bishop.vcxproj"
set "P_Goddess=%SRC%\MultiServer\Goddess\Goddess.vcxproj"
set "P_S3Relay=%SRC%\MultiServer\S3Relay\S3Relay.vcxproj"
set "P_S3RelayServer=%SRC%\Sword3PaySys\S3RELAYSERVER\S3RelayServer.vcxproj"
set "P_Sword3PaySys=%SRC%\Sword3PaySys\S3AccServer\Sword3PaySys.vcxproj"
set "P_Game=%SRC%\S3Client\S3Client.vcxproj"

rem First-run / missing binary detection and timestamp-based source detection.
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$root='%ROOT%';$src='%SRC%';$server='%SERVER%';$client='%CLIENT%';" ^
  "$map=@{" ^
  "GameServer=@((Join-Path $src 'MultiServer\GameServer'),(Join-Path $src 'MultiServer\Common'));" ^
  "Bishop=@((Join-Path $src 'MultiServer\Bishop'),(Join-Path $src 'MultiServer\Common'));" ^
  "Goddess=@((Join-Path $src 'MultiServer\Goddess'),(Join-Path $src 'MultiServer\Common'));" ^
  "S3Relay=@((Join-Path $src 'MultiServer\S3Relay'),(Join-Path $src 'MultiServer\Common'));" ^
  "S3RelayServer=@((Join-Path $src 'Sword3PaySys\S3RELAYSERVER'),(Join-Path $src 'MultiServer\Common'));" ^
  "Sword3PaySys=@((Join-Path $src 'Sword3PaySys\S3AccServer'),(Join-Path $src 'MultiServer\Common'));" ^
  "Game=@((Join-Path $src 'S3Client'),(Join-Path $src 'MultiServer\Common'))};" ^
  "$shared=@((Join-Path $src 'MultiServer\Common'),(Join-Path $src 'Core'),(Join-Path $src 'Engine'),(Join-Path $src 'Represent'),(Join-Path $src 'Library'));" ^
  "$exe=@{GameServer=(Join-Path $server 'GameServer.exe');Bishop=(Join-Path $server 'Bishop.exe');Goddess=(Join-Path $server 'Goddess.exe');S3Relay=(Join-Path $server 'S3Relay.exe');S3RelayServer=(Join-Path $server 'S3RelayServer.exe');Sword3PaySys=(Join-Path $server 'Sword3PaySys.exe');Game=(Join-Path $client 'Game.exe')};" ^
  "$out=@(); foreach($n in $map.Keys){$target=$exe[$n];$stamp=if(Test-Path $target){(Get-Item $target).LastWriteTimeUtc}else{[datetime]::MinValue};$changed=$false;foreach($d in $map[$n]){if(Test-Path $d){$f=Get-ChildItem $d -Recurse -File -Include *.cpp,*.c,*.h,*.hpp,*.inl,*.rc -ErrorAction SilentlyContinue;if($f){$m=($f|Measure-Object LastWriteTimeUtc -Maximum).Maximum;if($m -gt $stamp){$changed=$true}}}};foreach($d in $shared){if(Test-Path $d){$f=Get-ChildItem $d -Recurse -File -Include *.cpp,*.c,*.h,*.hpp,*.inl,*.rc -ErrorAction SilentlyContinue;if($f){$m=($f|Measure-Object LastWriteTimeUtc -Maximum).Maximum;if($m -gt $stamp){$changed=$true}}}};if($changed){$out+=$n}};Set-Content $env:TEMP\jx_dev_projects.txt $out -Encoding ASCII;Write-Host ('Changed: '+($out -join ', '))"

set "ANY=0"
for /f "usebackq delims=" %%P in ("%STATE%") do set "ANY=1"

if "%ANY%"=="0" goto ENSURE_ALL

echo [BUILD] Changed targets:
type "%STATE%"
echo.

rem Stop ONLY processes that actually need rebuilding.
for /f "usebackq delims=" %%P in ("%STATE%") do (
  echo [STOP] %%P.exe
  taskkill /F /IM %%P.exe >nul 2>&1
)

rem Build each changed project incrementally. MSBuild decides which .cpp files need recompiling.
for /f "usebackq delims=" %%P in ("%STATE%") do call :BUILD_ONE %%P
if errorlevel 1 goto FAIL

rem Restart only processes rebuilt above, in the normal server dependency order.
for %%P in (Sword3PaySys S3RelayServer Goddess Bishop S3Relay GameServer Game) do (
  powershell -NoProfile -Command "$n='%%P'; if((Get-Content -LiteralPath '%STATE%' -ErrorAction SilentlyContinue) -contains $n){$exe=if($n -eq 'Game'){'%CLIENT%\Game.exe'}else{'%SERVER%\'+$n+'.exe'};$dir=Split-Path $exe;$out='%DEVLOG%\'+$n+'.out.log';$err='%DEVLOG%\'+$n+'.err.log';$cmd='start "" /b "'+$exe+'" > "'+$out+'" 2> "'+$err+'"';Start-Process cmd.exe -WindowStyle Hidden -WorkingDirectory $dir -ArgumentList '/d','/c',$cmd}"
  timeout /t 2 /nobreak >nul
)
goto END

:BUILD_ONE
set "N=%~1"
set "PROJ=!P_%N%!"
if /i "%N%"=="Game" (
  echo [BUILD] Client Debug - S3Client.vcxproj
  "%MSBUILD%" "!PROJ!" /t:Build /p:Configuration=Debug /p:Platform=Win32 /m /nologo /v:minimal /fl1 /flp1:logfile="%LOG%\dev_client.log";verbosity=minimal
) else (
  echo [BUILD] Server Debug - %N%
  "%MSBUILD%" "!PROJ!" /t:Build /p:Configuration=Debug /p:Platform=Win32 /m /nologo /v:minimal /fl1 /flp1:logfile="%LOG%\dev_%N%.log";verbosity=minimal
)
if errorlevel 1 exit /b 1
exit /b 0

:ENSURE_ALL
echo [RUN] No source changes detected.
echo [RUN] Ensuring server processes are running in startup order...
for %%P in (Sword3PaySys S3RelayServer Goddess Bishop S3Relay GameServer) do (
  powershell -NoProfile -Command "if(-not (Get-Process -Name '%%P' -ErrorAction SilentlyContinue)){exit 1}else{exit 0}"
  if errorlevel 1 powershell -NoProfile -Command "$exe='%SERVER%\%%P.exe';$cmd='start "" /b "'+$exe+'" > "%DEVLOG%\%%P.out.log" 2> "%DEVLOG%\%%P.err.log"';Start-Process cmd.exe -WindowStyle Hidden -WorkingDirectory '%SERVER%' -ArgumentList '/d','/c',$cmd"
  timeout /t 2 /nobreak >nul
)
%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe -NoProfile -Command "if(-not (Get-Process -Name 'Game' -ErrorAction SilentlyContinue)){exit 1}else{exit 0}"
if errorlevel 1 powershell -NoProfile -Command "$exe='%CLIENT%\Game.exe';$cmd='start "" /b "'+$exe+'" > "%DEVLOG%\Game.out.log" 2> "%DEVLOG%\Game.err.log"';Start-Process cmd.exe -WindowStyle Hidden -WorkingDirectory '%CLIENT%' -ArgumentList '/d','/c',$cmd"
goto END

:FAIL
echo.
echo [ERROR] Incremental build failed. Only processes stopped for failed targets remain stopped.
echo [LOG] Check %LOG%
goto END

:END
echo.
echo ============================================================
echo   DONE - no JxStartup.exe is used
echo ============================================================
endlocal
