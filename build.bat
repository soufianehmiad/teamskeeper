@echo off
echo Building TeamsKeeper for Windows...

if not exist "build" mkdir build
cd build

echo Configuring CMake...
cmake .. -G "Visual Studio 17 2022" -A x64

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo Building project...
cmake --build . --config Release

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
echo Executable: build\Release\TeamsKeeper.exe
pause