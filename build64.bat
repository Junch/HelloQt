@echo off

rem Usage: build64.bat [Debug|Release] | clean | help
setlocal enableextensions enabledelayedexpansion

set "config=%~1"
if /i "%config%"=="" set "config=Release"

if /i "%config%"=="clean" goto CLEAN
if /i "%config%"=="help" goto HELP

set "folder=build"

rem Create build folder and enter
if not exist "%folder%" mkdir "%folder%" >nul 2>&1
pushd "%folder%" >nul

echo Building with configuration: %config%

rem Try to find Visual Studio and set x64 env (optional)
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
	for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2^>nul`) do set "VSINSTALL=%%i"
)
if defined VSINSTALL (
	echo Found Visual Studio at %VSINSTALL% - configuring x64 toolset
	call "%VSINSTALL%\VC\Auxiliary\Build\vcvarsall.bat" amd64 >nul
) else (
	echo Note: Visual Studio installation not found via vswhere; ensure an x64 dev environment is active if needed.
)

rem Configure & build (no -A x64 for Ninja; x64 comes from the environment)
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE="%config%" ..
cmake --build . --config "%config%"

popd >nul
goto END

:CLEAN
echo Removing "%folder%" ...
rd "%folder%" /s /q
goto END

:HELP
echo Usage: build64.bat [Debug^|Release] ^| clean ^| help
echo  - If you need 64-bit MSVC, run this from an "x64 Native Tools" prompt
echo  - The script will attempt to call vcvarsall amd64 if it can find Visual Studio via vswhere
goto END

:END
pause