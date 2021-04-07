
cls
rem Here we set some variables that are not set by Easy-build.cmd/razzle during load, so we just load them
set Easy-Build-Version=v0.1-Win2K
set CHECKED_ALT_DIR=
set BUILD_ALT_DIR=
set DBG=
if /i "%_BINPLACE_DIR%" == "" set  _BINPLACE_DIR=%_NTROOT%\binaries
if /i "%1" == "" set "_BINPLACE_SUBDIR=free" && set "FREEBUILD=1" && call setfre.cmd
if /i "%1" == "free" set "_BINPLACE_SUBDIR=free" && set "FREEBUILD=1" && call setfre.cmd
if /i "%1" == "chk" set "_BINPLACE_SUBDIR=checked" && set "FREEBUILD=0" && call setchk.cmd
if /i "%NTDEBUG%" == "" set NTDEBUG=ntsdnodbg
if /i "%_BINPLACE_SUBDIR%" == "" call setfre.cmd
if "%_NT386TREE%" == "" set _NT386TREE=%_BINPLACE_DIR%\%_BINPLACE_SUBDIR%
goto eb-NT-mainmenu


:eb-NT-mainmenu
cls
Title Easy-Build Razzle Environment for Windows 2000 %Easy-Build-Version%
if /i "%_BINPLACE_SUBDIR%" == "free" set ErrorLogsEB=%_NTDrive%%_NTROOT%\private\build.err
if /i "%_BINPLACE_SUBDIR%" == "checked" set ErrorLogsEB=%_NTDrive%%_NTROOT%\private\buildd.err
if /i "%_BINPLACE_SUBDIR%" == "free" set WarningLogsEB=%_NTDrive%%_NTROOT%\private\build.wrn
if /i "%_BINPLACE_SUBDIR%" == "checked" set WarningLogsEB=%_NTDrive%%_NTROOT%\private\buildd.wrn
cd /d  %_NTDrive%%_NTROOT%
echo -------------------------------------------------------------------------------------------------------------------
echo  Easy-Build Razzle Environment (Very limited features currently, WIP)
echo -------------------------------------------------------------------------------------------------------------------
echo  Build User: %_NTUSER%	Build Machine: %COMPUTERNAME%
echo  Build Root: %_NTDrive%%_NTROOT%	Razzle Tool Path: %_NTDrive%%_NTROOT%\public\tools
echo  Postbuild Dir: %_NTDrive%%_NTROOT%\Binaries
echo -------------------------------------------------------------------------------------------------------------------
echo  Release Type: %_BINPLACE_SUBDIR%  -  NT Ver: %BUILD_PRODUCT% %BUILD_PRODUCT_VER%  -  
echo -------------------------------------------------------------------------------------------------------------------
echo  Work in progress
echo  Currently it has many issues, some missing includes, issues finding .tmp files..
echo.
echo -------------------------------------------------------------------------------------------------------------------
echo  1) Clean Build (Full err path, delete object files)
echo  2) 'Dirty' Build (Full err path, no checks)
echo  3) Build Specific Directory Only
echo  b/w) Open Build Error or Warning Logs
echo -------------------------------------------------------------------------------------------------------------------
echo  r) Drop to Razzle Prompt 
echo.
echo ___________________________________________________________________________________________________________________
set /p NTMMENU=Select:
echo ___________________________________________________________________________________________________________________
if /i "%NTMMENU%"=="1" goto cleanbuild
if /i "%NTMMENU%"=="2" goto DirtyBuild
if /i "%NTMMENU%"=="b" cmd.exe /c notepad %ErrorLogsEB%
if /i "%NTMMENU%"=="w" cmd.exe /c notepad %WarningLogsEB%
if /i "%NTMMENU%"=="3" goto SpecificBLD
if /i "%NTMMENU%"=="r" exit /b
if /i "%NTMMENU%"=="var" set && pause && goto eb-NT-mainmenu
if /i "%NTMMENU%"=="options" goto BuildOptions
goto eb-NT-mainmenu

:cleanbuild
cls
cd /d %_NTDrive%%_NTROOT%\private
build -bcDeFZP
pause
goto eb-NT-mainmenu
:DirtyBuild
cls
cd /d %_NTDrive%%_NTROOT%\private
build -bDeFZP
pause
goto eb-NT-mainmenu


:SpecificBLD
cls
echo ----------------------------------------------------------------------
echo This section we can clean build certain components of the source
echo So if you want to rebuild the Kernel you would type:
echo.
echo F:\NT\private\ntos
echo ----------------------------------------------------------------------
echo.
echo Type full path to folder or type back to return:
echo.
set /p userinput=:
if "%userinput%"=="back" goto eb-NT-mainmenu
cd /d %userinput%
echo BUILD: %CD% STARTED
echo.
build -bcDeFZP
pause
goto eb-NT-mainmenu

