
setlocal enabledelayedexpansion
cd /d %~dp0
for /D /R . %%D IN ("obj\") do @IF EXIST "%%D" rd /S /Q "%%D"
for /D /R . %%D IN ("objd\") do @IF EXIST "%%D" rd /S /Q "%%D"
