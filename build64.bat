@echo off 
set config=Release
set folder=_build-x64

if "%1" == "clean" goto CLEAN

@mkdir %folder% >nul
pushd %folder% >nul

@echo on

cmake -A x64 .. -DCMAKE_PREFIX_PATH="C:/Qt/Qt5.6.3/5.6.3/msvc2015_64/lib/cmake/Qt5"
cmake --build . --config %config%

@echo off
popd >nul
goto END

:CLEAN
rd %folder% /s/q
goto END

:END
pause