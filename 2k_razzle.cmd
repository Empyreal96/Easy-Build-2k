@echo off
cd /d %~d0
REM
REM UAC elevation
REM I found this method to elevate the script to admin here: https://stackoverflow.com/a/12264592
REM I chose it because it is what my Windows 10 Toolbox uses, and works well!
REM
:init
 setlocal DisableDelayedExpansion
 set cmdInvoke=1
 set winSysFolder=System32
 set "batchPath=%~0"
 for %%k in (%0) do set batchName=%%~nk
 set "vbsGetPrivileges=%temp%\OEgetPriv_%batchName%.vbs"
 setlocal EnableDelayedExpansion

:checkPrivileges
  NET FILE 1>NUL 2>NUL
  if '%errorlevel%' == '0' ( goto gotPrivileges ) else ( goto getPrivileges )

:getPrivileges
  if '%1'=='ELEV' (echo ELEV & shift /1 & goto gotPrivileges)
  ECHO.
  ECHO.
  ECHO Invoking UAC for Privilege Escalation
  ECHO.

  ECHO Set UAC = CreateObject^("Shell.Application"^) > "%vbsGetPrivileges%"
  ECHO args = "ELEV " >> "%vbsGetPrivileges%"
  ECHO For Each strArg in WScript.Arguments >> "%vbsGetPrivileges%"
  ECHO args = args ^& strArg ^& " "  >> "%vbsGetPrivileges%"
  ECHO Next >> "%vbsGetPrivileges%"

  if '%cmdInvoke%'=='1' goto InvokeCmd 

  ECHO UAC.ShellExecute "!batchPath!", args, "", "runas", 1 >> "%vbsGetPrivileges%"
  goto ExecElevation

:InvokeCmd
  ECHO args = "/c """ + "!batchPath!" + """ " + args >> "%vbsGetPrivileges%"
  ECHO UAC.ShellExecute "%SystemRoot%\%winSysFolder%\cmd.exe", args, "", "runas", 1 >> "%vbsGetPrivileges%"

:ExecElevation
 "%SystemRoot%\%winSysFolder%\WScript.exe" "%vbsGetPrivileges%" %*
 exit /B

:gotPrivileges
 setlocal & cd /d %~dp0
 if '%1'=='ELEV' (del "%vbsGetPrivileges%" 1>nul 2>nul  &  shift /1)

:ebinit
if NOT exist "%~dp0\easy-build_1strun.complete" goto eb-start
if exist "%~dp0\easy-build_1strun.complete" goto eb-nt-checks

:eb-start
cd /d %~dp0
Title Easy-Build Environment for Windows 2000
echo --------------------------------------------------------
echo Welcome to Windows 2000..
echo.
echo -- Early test version --
echo Note: Razzle is ported over from the Xbox tree.
echo Majority of header files taken from Win2000 DDk/SDK's
echo.
echo --------------------------------------------------------
pause
echo First run complete! delete this file to show 'First Run' screen >> %~dp0\easy-build_1strun.complete
goto eb-nt-checks

:eb-nt-checks
if not exist "%~d0\nt" echo %~d0\NT not found && pause && exit /b
REM
REM ADD CHECK FOR ALREADY PATCHED SOURCE OR IF TO BE PATCHED
if NOT exist "%~d0\nt\PRIVATE\DEVELOPR\%username%\" (goto eb-setup-profile) else (goto eb-mainmenu-init)
REM
REM


:eb-setup-profile
if exist "%~d0\NT\PRIVATE\DEVELOPR\%username%\" echo Profile already created && goto xbox-dorazzle
echo.
echo Creating Razzle profile
cd /d %~d0\NT\PRIVATE\DEVELOPR\TEMPLATE\
goto eb-initrazzle


REM Contents of 'xbox\private\developr\template\initrazzle.cmd' adapted for Easy-Build
:eb-initrazzle
 
setlocal
set _drive_=%~d0
set _ntroot_=nt

set _drive_=ntroot
if /i "%_drive%" == "ntroot" set _ntroot_=nt& shift& shift

xcopy /f %~d0\nt\private\developr\template %~d0\nt\private\developr\%username%\
cd /d %~d0\nt\private\developr\%username%
move cuep-sample.pri cuep.pri
move setenvp-sample.cmd setenvp.cmd
move setchkp-sample.cmd setchkp.cmd
move setfrep-sample.cmd setfrep.cmd
move tools-sample.ini tools.ini
set _ntdrive=%_drive_%
set _ntbindir=%_drive_%\%_ntroot_%

endlocal
echo Loading Razzle
goto eb-mainmenu-init

:eb-mainmenu-init
cd /d %~d0\NT\PRIVATE\DEVELOPR\%username%\
goto dorazzle

REM Contents of 'xbox\private\developr\%username%\dorazzle.cmd' adapted for Easy-Build
rem fixed the invalid paths to 'idw' and 'mstools'

:dorazzle

REM
REM Set _NTDrive
REM
set _NTDrive=%~d0
REM
REM Set _NTRoot
REM
set _NTRoot=\nt
REM
REM Support Win64
REM
if /i "%1" == "WIN64" (
	set _NTWIN64=1
	shift
)
REM
REM Add MSTOOLS, IDW and PUBLIC\TOOLS to the path if not in system directory.
REM
if exist %_NTDrive%%_NTRoot%\public\mstools (
    set MSTOOLS_DIR=%_NTDrive%%_NTRoot%\public\mstools
    set PATH=%PATH%;%_NTDrive%%_NTRoot%\public\mstools
)
if exist %_NTDrive%%_NTRoot%\public\idw (
    set IDW_DIR=%_NTDrive%%_NTRoot%\public\idw
    set PATH=%PATH%;%_NTDrive%%_NTRoot%\public\idw
)
if exist %_NTDrive%%_NTRoot%\public\tools (
    set PATH=%PATH%;%_NTDrive%%_NTRoot%\public\tools
)

goto ebhandover

:ebhandover

rem
rem
cls
echo.
echo Razzle will now start.
echo. 
echo Please type "easybuild fre" or "easybuild chk" without quotes
echo.
echo All that can be done so far is building the tree.
echo.
pause
goto INVOKEIT
:INVOKEIT
REM
REM Invoke RAZZLE.CMD, which does the real work of setting up the Razzle window.
REM

if /i "%PROCESSOR_ARCHITECTURE%" == "AMD64" SET PROCESSOR_ARCHITECTURE=x86
cls
cmd.exe /k "%_NTDrive%%_NTRoot%\public\tools\razzle.cmd %~d0 NTROOT \NT SETFRE"