$ErrorActionPreference='Stop'
$port=18770
$root=$PSScriptRoot
$src=Join-Path $root 'SwordOnline\Sources'
$runtime='D:\games\bin\bin'; $server=Join-Path $runtime 'Server'; $client=Join-Path $runtime 'client'
$configFile=Join-Path $root 'devcenter.config.json'
if(Test-Path $configFile){try{$cfg=Get-Content $configFile -Raw|ConvertFrom-Json;if($cfg.ServerRuntime){$server=$cfg.ServerRuntime};if($cfg.ClientRuntime){$client=$cfg.ClientRuntime}}catch{}}
$logDir=Join-Path $root 'devlogs'; New-Item -ItemType Directory -Force $logDir | Out-Null
$msbuild='C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe'
$fullscreenType=@'
using System;
using System.Runtime.InteropServices;
public static class JXDevWindow {
  [DllImport("user32.dll")] static extern int GetWindowLong(IntPtr hWnd, int nIndex);
  [DllImport("user32.dll")] static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
  [DllImport("user32.dll")] static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, uint flags);
  const int GWL_STYLE=-16, GWL_EXSTYLE=-20;
  const int WS_VISIBLE=0x10000000, WS_OVERLAPPEDWINDOW=0x00CF0000;
  const int WS_EX_APPWINDOW=0x00040000;
  static readonly IntPtr HWND_TOP=new IntPtr(0);
  const uint SWP_FRAMECHANGED=0x0020, SWP_SHOWWINDOW=0x0040, SWP_NOACTIVATE=0x0010, SWP_NOMOVE=0x0002, SWP_NOSIZE=0x0001;
  public static void MakeWindowed(IntPtr hWnd) {
    if(hWnd==IntPtr.Zero) return;
    SetWindowLong(hWnd,GWL_STYLE,WS_VISIBLE|WS_OVERLAPPEDWINDOW);
    SetWindowLong(hWnd,GWL_EXSTYLE,WS_EX_APPWINDOW);
    int width=816, height=638;
    SetWindowPos(hWnd,HWND_TOP,(1920-width)/2,(1080-height)/2,width,height,SWP_FRAMECHANGED|SWP_SHOWWINDOW|SWP_NOACTIVATE);
  }
}
'@
try { Add-Type -TypeDefinition $fullscreenType -ErrorAction Stop } catch { }
function MakeGameWindowed($p){if($p -and $p.MainWindowHandle -ne 0){[JXDevWindow]::MakeWindowed($p.MainWindowHandle)}}
$names=@('Sword3PaySys','S3RelayServer','Goddess','Bishop','S3Relay','GameServer','Game')
$projects=[ordered]@{
 GameServer=(Join-Path $src 'MultiServer\GameServer\GameServer.vcxproj'); Bishop=(Join-Path $src 'MultiServer\Bishop\Bishop.vcxproj'); Goddess=(Join-Path $src 'MultiServer\Goddess\Goddess.vcxproj'); S3Relay=(Join-Path $src 'MultiServer\S3Relay\S3Relay.vcxproj'); S3RelayServer=(Join-Path $src 'Sword3PaySys\S3RELAYSERVER\S3RelayServer.vcxproj'); Sword3PaySys=(Join-Path $src 'Sword3PaySys\S3AccServer\Sword3PaySys.vcxproj'); Game=(Join-Path $src 'S3Client\S3Client.vcxproj')
}
$sourceDirs=@{
 GameServer=@((Join-Path $src 'MultiServer\GameServer'),(Join-Path $src 'MultiServer\Common')); Bishop=@((Join-Path $src 'MultiServer\Bishop'),(Join-Path $src 'MultiServer\Common')); Goddess=@((Join-Path $src 'MultiServer\Goddess'),(Join-Path $src 'MultiServer\Common')); S3Relay=@((Join-Path $src 'MultiServer\S3Relay'),(Join-Path $src 'MultiServer\Common')); S3RelayServer=@((Join-Path $src 'Sword3PaySys\S3RELAYSERVER'),(Join-Path $src 'MultiServer\Common')); Sword3PaySys=@((Join-Path $src 'Sword3PaySys\S3AccServer'),(Join-Path $src 'MultiServer\Common')); Game=@((Join-Path $src 'S3Client'),(Join-Path $src 'MultiServer\Common'))
}
$shared=@((Join-Path $src 'MultiServer\Common'),(Join-Path $src 'Core'),(Join-Path $src 'Engine'),(Join-Path $src 'Represent'),(Join-Path $src 'Library'))
function Exe($n){if($n -eq 'Game'){Join-Path $client 'Game.exe'}else{Join-Path $server ($n+'.exe')}}
function IsRunning($n){return [bool](Get-Process -Name $n -ErrorAction SilentlyContinue)}
function AppendLog($n,$message){$f=Join-Path $logDir ($n+'.out.log');Add-Content -LiteralPath $f -Value ("[{0}] {1}" -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'),$message) -Encoding UTF8}
function StopOne($n){$p=Get-Process -Name $n -ErrorAction SilentlyContinue;if($p){$p | Stop-Process -Force;AppendLog $n 'Process stopped'}}
function StartOne($n){$exe=Exe $n;if(!(Test-Path $exe)){AppendLog $n "Missing executable: $exe";return @{ok=$false;message="Missing $exe"}};$dir=Split-Path $exe;$windowStyle=if($n -eq 'Game'){'Normal'}else{'Hidden'};try{$p=Start-Process -FilePath $exe -WorkingDirectory $dir -WindowStyle $windowStyle -PassThru}catch{AppendLog $n "Launch error: $($_.Exception.Message)";return @{ok=$false;message="$n launch error: $($_.Exception.Message)"}};AppendLog $n ("Process launched, PID {0}, WindowStyle {1}" -f $p.Id,$windowStyle);for($i=0;$i -lt 15;$i++){Start-Sleep -Seconds 1;if(!$p.HasExited){Start-Sleep -Seconds 1;if(!$p.HasExited){AppendLog $n 'Process is running and stable';return @{ok=$true;message="$n started and stable"}}}else{AppendLog $n ("Process exited during startup, exit {0}" -f $p.ExitCode);break}};return @{ok=$false;message="$n exited during startup (exit $($p.ExitCode))"}}
function SaveConfig($s,$c){([ordered]@{ServerRuntime=$s;ClientRuntime=$c}|ConvertTo-Json)|Set-Content $configFile -Encoding UTF8;$script:server=$s;$script:client=$c}
function ChangedTargets{$result=@();foreach($n in $projects.Keys){$stamp=if(Test-Path (Exe $n)){(Get-Item (Exe $n)).LastWriteTimeUtc}else{[datetime]::MinValue};$changed=$false;foreach($d in @($sourceDirs[$n])+$shared){if(Test-Path $d){$f=Get-ChildItem $d -Recurse -File -Include *.cpp,*.c,*.h,*.hpp,*.inl,*.rc -ErrorAction SilentlyContinue;if($f){$m=($f|Measure-Object LastWriteTimeUtc -Maximum).Maximum;if($m -gt $stamp){$changed=$true}}}};if($changed){$result+=$n}};return $result}
function BuildOne($n){$log=Join-Path $logDir ($n+'.build.log');& $msbuild $projects[$n] '/t:Build' '/p:Configuration=Debug' '/p:Platform=Win32' '/m' '/nologo' '/v:minimal' 2>&1 | Tee-Object -FilePath $log;return ($LASTEXITCODE -eq 0)}
function BuildChanged{$changed=ChangedTargets;if(!$changed){return @()};foreach($n in $changed){StopOne $n};foreach($n in $changed){if(!(BuildOne $n)){return $changed}};foreach($n in $names){if($changed -contains $n){$null=StartOne $n;Start-Sleep -Seconds 2}};return $changed}
function StartAll{$results=@();foreach($n in $names){if(!(IsRunning $n)){$r=StartOne $n;$results+=([ordered]@{name=$n;ok=$r.ok;message=$r.message});if(!$r.ok){break}}else{$results+=([ordered]@{name=$n;ok=$true;message="$n already running"})}};return $results}
function Status{$a=@();foreach($n in $names){$p=Get-Process -Name $n -ErrorAction SilentlyContinue;$a+=([ordered]@{name=$n;running=[bool]$p;pid=if($p){$p.Id}else{$null}})};return $a}
function NativeLog($n){$base=if($n -eq 'Game'){Join-Path $client 'ui_layout.log'}elseif($n -eq 'Sword3PaySys'){Join-Path $server 'logs\paysys'}elseif($n -eq 'S3RelayServer'){Join-Path $server 'relayserver_log'}elseif($n -eq 'Goddess'){Join-Path $server 'logs\goddess'}elseif($n -eq 'Bishop'){Join-Path $server 'logs\bishop'}elseif($n -eq 'S3Relay'){Join-Path $server 'logs\relay'}else{$null};if(!$base -or !(Test-Path $base)){return @()};if(Test-Path $base -PathType Leaf){return Get-Content $base -Tail 180 -ErrorAction SilentlyContinue};$f=Get-ChildItem $base -Recurse -File -ErrorAction SilentlyContinue | Sort-Object LastWriteTime -Descending | Select-Object -First 1;if($f){return Get-Content $f.FullName -Tail 180 -ErrorAction SilentlyContinue};return @()}
$html=@'
<!doctype html><html><head><meta charset="utf-8"><title>JX2022 Dev Center</title><style>
*{box-sizing:border-box}body{margin:0;background:#0e1116;color:#d7dde7;font:13px system-ui,Segoe UI,sans-serif}header{padding:14px 18px;background:#171b22;border-bottom:1px solid #303641;position:sticky;top:0;z-index:2}h1{font-size:18px;margin:0}.sub{color:#8792a2;font-size:12px;margin-top:3px}.bar{display:flex;gap:8px;padding:12px 18px;background:#12161c;position:sticky;top:61px;z-index:2;border-bottom:1px solid #252b34}button{background:#252c36;color:#eee;border:1px solid #414a57;border-radius:6px;padding:8px 13px;cursor:pointer}button:hover{background:#303946}button.danger{border-color:#81404a}.grid{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:10px;padding:12px}.card{background:#151a21;border:1px solid #2c333d;border-radius:7px;overflow:hidden}.head{display:flex;justify-content:space-between;padding:8px 10px;background:#1c222b}.dot{font-size:11px}.on{color:#72d68a}.off{color:#e06c75}.log{height:260px;margin:0;padding:10px;overflow:auto;white-space:pre-wrap;font:12px Consolas,monospace;color:#bfc7d4}.selected{outline:1px solid #667085}@media(max-width:900px){.grid{grid-template-columns:1fr}}</style></head><body>
<div style="padding:10px 18px;background:#10141a;border-bottom:1px solid #252b34"><b>Startup order</b><span style="color:#8792a2"> 1 Sword3PaySys -&gt; 2 S3RelayServer -&gt; 3 Goddess -&gt; 4 Bishop -&gt; 5 S3Relay -&gt; 6 GameServer -&gt; 7 Game</span><div class="sub">Next service starts only after the previous process is confirmed alive and stable.</div></div>
<header><h1>JX2022 Dev Center</h1><div class="sub">Incremental build · service control · continuous logs</div></header>
<nav style="padding:10px 18px;background:#12161c;border-bottom:1px solid #252b34"><button onclick="tab('services')">Services</button><button onclick="tab('config')">Config</button></nav><div id="services"><div class="bar"><button onclick="api('/api/start')">Start All</button><button onclick="api('/api/client')">Start Client</button><button onclick="api('/api/build')">Incremental Build</button><button onclick="api('/api/stop')" class="danger">Stop All</button><button onclick="api('/api/refresh')">Refresh</button><span id="msg" class="sub"></span></div><div class="grid" id="grid"></div></div><div id="config" style="display:none;padding:18px"><h2>Runtime Config</h2><p class="sub">Configure server and client runtime folders.</p><label>Server runtime<br><input id="server" style="width:80%;padding:9px;background:#151a21;color:#eee;border:1px solid #414a57"></label><br><br><label>Client runtime<br><input id="client" style="width:80%;padding:9px;background:#151a21;color:#eee;border:1px solid #414a57"></label><br><br><button onclick="saveConfig()">Save Config</button><span id="cfgmsg" class="sub"></span></div>
<script>const names=['Sword3PaySys','S3RelayServer','Goddess','Bishop','S3Relay','GameServer','Game'];const g=document.getElementById('grid');for(const [i,n] of names.entries())g.insertAdjacentHTML('beforeend',`<section class="card"><div class="head"><b>${i+1}. ${n}</b><span id="s-${n}" class="dot off">STOPPED</span></div><pre id="l-${n}" class="log">Waiting...</pre></section>`);function tab(x){document.getElementById('services').style.display=x==='services'?'block':'none';document.getElementById('config').style.display=x==='config'?'block':'none';if(x==='config')loadConfig()}async function api(u){document.getElementById('msg').textContent='Working...';try{let r=await fetch(u,{method:'POST'});let d=await r.json();document.getElementById('msg').textContent=d.message||'Done';refresh()}catch(e){document.getElementById('msg').textContent='Error: '+e.message}}async function refresh(){try{let r=await fetch('/api/status?x='+Date.now());let d=await r.json();for(const x of d.status){let e=document.getElementById('s-'+x.name);e.textContent=x.running?'RUNNING':'STOPPED';e.className='dot '+(x.running?'on':'off')}for(const n of names){let r=await fetch('/logs/'+n+'?x='+Date.now()),t=await r.text(),e=document.getElementById('l-'+n),at=e.scrollTop+e.clientHeight>=e.scrollHeight-25;e.textContent=t||'(no output)';if(at)e.scrollTop=e.scrollHeight}}catch(e){document.getElementById('msg').textContent='Connection error: '+e.message}}async function loadConfig(){try{let r=await fetch('/api/config?x='+Date.now()),d=await r.json();document.getElementById('server').value=d.server||'';document.getElementById('client').value=d.client||''}catch(e){document.getElementById('cfgmsg').textContent='Load failed'}}async function saveConfig(){let s=document.getElementById('server').value.trim(),c=document.getElementById('client').value.trim();if(!s||!c){document.getElementById('cfgmsg').textContent='Both paths are required';return}try{let r=await fetch('/api/config',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({server:s,client:c})});let d=await r.json();document.getElementById('cfgmsg').textContent=d.message||'Saved'}catch(e){document.getElementById('cfgmsg').textContent='Save failed: '+e.message}}loadConfig();refresh();setInterval(refresh,1200)</script></body></html>
'@
$listener=New-Object Net.HttpListener;$listener.Prefixes.Add("http://localhost:$port/");$listener.Start()
while($listener.IsListening){$ctx=$listener.GetContext();$path=$ctx.Request.Url.AbsolutePath;$method=$ctx.Request.HttpMethod;$body='';
 if($path -eq '/api/start' -and $method -eq 'POST'){$r=StartAll;$ok=($r | Where-Object {!$_.ok}).Count -eq 0;$body=(@{message=if($ok){'Startup sequence completed'}else{'Startup stopped: '+(($r|Where-Object {!$_.ok})[0].message)};results=$r;status=Status}|ConvertTo-Json -Depth 6)}
 elseif($path -eq '/api/stop' -and $method -eq 'POST'){foreach($n in $names){StopOne $n};$body=(@{message='All services stopped'}|ConvertTo-Json)}
 elseif($path -eq '/api/build' -and $method -eq 'POST'){$c=BuildChanged;$body=(@{message=if($c.Count){'Built: '+($c -join ', ')}else{'Nothing to build'};changed=$c}|ConvertTo-Json -Depth 5)}
 elseif($path -eq '/api/refresh' -and $method -eq 'POST'){$r=StartAll;$body=(@{message='Refresh/start sequence complete';results=$r;status=Status}|ConvertTo-Json -Depth 6)}
 elseif($path -eq '/api/status'){$body=(@{status=Status}|ConvertTo-Json -Depth 5)}
 elseif($path -eq '/api/client' -and $method -eq 'POST'){$r=StartOne 'Game';$body=(@{message=$r.message;result=$r;status=Status}|ConvertTo-Json -Depth 5)}
 elseif($path -eq '/api/config' -and $method -eq 'GET'){$body=(@{server=$server;client=$client}|ConvertTo-Json)}
 elseif($path -eq '/api/config' -and $method -eq 'POST'){$reader=New-Object IO.StreamReader($ctx.Request.InputStream);$j=$reader.ReadToEnd()|ConvertFrom-Json;SaveConfig $j.server $j.client;$body=(@{message='Config saved';server=$server;client=$client}|ConvertTo-Json)}
 elseif($path -like '/logs/*'){$n=$path.Substring(6);$o=Join-Path $logDir ($n+'.out.log');$a=if(Test-Path $o){Get-Content $o -Tail 80}else{@()};$b=NativeLog $n;$body=[string]::Join("`n",@($a)+@('--- native log ---')+@($b))}
 else{$body=$html}
 $bytes=[Text.Encoding]::UTF8.GetBytes($body);$ctx.Response.ContentType=if($path -like '/api/*' -or $path -like '/logs/*'){'application/json; charset=utf-8'}else{'text/html; charset=utf-8'};if($path -like '/logs/*'){$ctx.Response.ContentType='text/plain; charset=utf-8'};$ctx.Response.ContentLength64=$bytes.Length;$ctx.Response.OutputStream.Write($bytes,0,$bytes.Length);$ctx.Response.Close()
}

